/*
 * @Author: fieryheart
 * @Date: 2019-06-06 10:48:12
 * @LastEditTime: 2019-06-06 12:07:00
 * @Description: This program is based on OpenCV and dlib.
 * @Description: If you find and bugs, please email me: fiery_heart@163.com
 */

#include "./src/FaceRecognition.h";

int main()
{
    FaceRecognition project;
    project.SetCameraCapture(0, 480, 320);
    project.LaunchCamera();
    return 0;
}