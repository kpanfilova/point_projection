#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d.hpp>
#include <iostream>

cv::Point3f sphere_to_cartesian(const float ro, const float theta, const float phi);
cv::Point3f cartesian_to_sphere(const cv::Point3f &point);
cv::Mat convert_degree_to_radian(const cv::Point3f &point);

cv::Point project_point_between_cameras(
    const cv::Point   &point_in_a_uv,
    float distance_to_a,
    const cv::Point3f &location_a,
    const cv::Point3f &rotation_a,
    const cv::Point3f &location_b,
    const cv::Point3f &rotation_b,
    int img_width,
    int img_height
);