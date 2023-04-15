
#include "headers.hpp"

int main()
{
    cv::Point point_in_a_uv(1000, 539);
    cv::Point3f location_a(0.0f, -5.87568f, 3.09466f);
    cv::Point3f rotation_a(90.0f, 0.0f, 0.0f);
    cv::Point3f location_b(4.28477f, -0.081509f, 5.33346f);
    cv::Point3f rotation_b(90.0f, 0.0f, 0.0f);
    cv::Point3f location_point(0.0f, 0.0f, 2.36024f);
    int img_w = 2000;
    int img_h = 1000;

    cv::Point3f diff = location_point - location_a;
    float distance_to_a = sqrt(diff.x * diff.x + diff.y * diff.y + diff.z * diff.z);

    cv::Point point_in_b_uv = project_point_between_cameras(point_in_a_uv, distance_to_a, location_a, rotation_a, 
                                                            location_b, rotation_b, img_w, img_h);

    std::cout << "coord = (" << point_in_b_uv.x << ", " << point_in_b_uv.y << ");\n";
    return 0;
}