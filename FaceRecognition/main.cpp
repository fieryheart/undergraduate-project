/*
 * @Author: fieryheart
 * @Date: 2019-06-06 10:48:12
 * @LastEditTime: 2019-06-06 14:23:38
 * @Description: This program is based on OpenCV and dlib.
 * @Description: If you find and bugs, please email me: fiery_heart@163.com
 */

#include "./src/FaceRecognition.h"

using namespace cv;
using namespace dlib;

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
        // image = project.DetectFace(image);
        win.clear_overlay();
        win.set_image(image);
        if(waitKey(30) >= 0) break;
    }
     
    return 0;
}