#include "headers.hpp"

cv::Point3f sphere_to_cartesian(const float ro, const float theta, const float phi)
{
    cv::Point3f xyz(ro * sin(phi) * cos(theta), ro * sin(phi) * sin(theta), ro * cos(phi));
    return xyz;
}

cv::Point3f cartesian_to_sphere(const cv::Point3f &point)
{
    float ro_b = sqrt(point.x * point.x + point.y * point.y + point.z * point.z);

    cv::Point3f sphere(ro_b, atan2(point.y, point.x), acos(point.z / ro_b));
    return sphere;
}

cv::Mat convert_degree_to_radian(const cv::Point3f &point)
{
    cv::Point3f rad_point = point * (CV_PI / 180.0);
    return cv::Mat_<float>(3,1) << rad_point.x, rad_point.y, rad_point.z;
}

cv::Point project_point_between_cameras(const cv::Point &point_in_a_uv, float distance_to_a, const cv::Point3f &location_a, 
                                        const cv::Point3f &rotation_a, const cv::Point3f &location_b, 
                                        const cv::Point3f &rotation_b, int img_width, int img_height)
{
    // create rotate matrix for rotate vector
    cv::Mat rotation_vector_a = convert_degree_to_radian(rotation_a); // function cv::Rodrigues use radian information
    cv::Mat rotation_vector_b = convert_degree_to_radian(rotation_b);
    cv::Mat rotation_matrix_a;
    cv::Mat rotation_matrix_b;
    cv::Rodrigues(rotation_vector_a, rotation_matrix_a); // (vector 3x1 -> matrix 3x3)
    cv::Rodrigues(rotation_vector_b, rotation_matrix_b);
 
    // ro, phi, theta from a_uv; ro = distance_to_a
    float theta = 2 * CV_PI * (point_in_a_uv.x) / img_width; //longitude (0; 2pi) (point_in_a_uv.x / img_width -> [0; 1])
    float phi = CV_PI * (point_in_a_uv.y) / img_height; // latitude (0; pi)

    // convert ro, phi, theta to xyz
    // center (0,0,0) is Camera A
    cv::Point3f point_a = sphere_to_cartesian(distance_to_a, theta, phi);
    
    // rotate xyz with rotation of camera A
    cv::Mat xyz_rot = rotation_matrix_a * (convert_degree_to_radian(point_a));
    cv::Point3f rot_point(xyz_rot);
    
    // change original coord to center of Camera B
    cv::Point3f change_point = rot_point - (location_a - location_b);
    
    // rotate xyz with rotation of camera B
    xyz_rot = rotation_matrix_b.t() * (cv::Mat_<float>(3,1) << change_point.x, change_point.y, change_point.z);
    cv::Point3f rot_point_b(xyz_rot);

    // to sphere coordinte; (ro, theta, phi)
    cv::Point3f new_point_b = cartesian_to_sphere(rot_point_b);
    
    // sphere coord to uv
    float u2 = new_point_b.y * img_width / (2 * CV_PI); //longitude (0; 2pi)
    float v2 = new_point_b.z * img_height / CV_PI;
    
    cv::Point result(static_cast<int>(u2), static_cast<int>(v2));

    return result;
}
