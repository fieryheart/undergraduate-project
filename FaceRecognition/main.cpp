/*
 * @Author: fieryheart
 * @Date: 2019-06-06 10:48:12
 * @LastEditTime: 2019-06-06 17:45:06
 * @Description: This program is based on OpenCV and dlib.
 * @Description: If you find and bugs, please email me: fiery_heart@163.com
 */

#include "./src/FaceRecognition.h"

using namespace cv;
using namespace dlib;
using namespace std;

int main()
{
    FaceRecognition project;
    image_window win;
    
    project.SetCameraCapture(0, 480, 320);
    
    // Test: Starting Camera
    // project.LaunchCamera();
    
    while(1) {
        Mat frame = project.GetCamreaFrame();
        matrix<bgr_pixel> image;
        image = project.MatToMatrix(frame);
        std::vector<dlib::rectangle> dets = project.DetectFace(image);
        win.clear_overlay();
        win.set_image(image);
        // win.add_overlay(dets, bgr_pixel(0,0,255));
        if(waitKey(30) >= 0) break;
    }

    return 0;
}