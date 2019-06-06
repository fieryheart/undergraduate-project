/*
 * @Author: fieryheart
 * @Date: 2019-06-06 10:50:53
 * @LastEditTime: 2019-06-06 14:23:44
 * @Description: This program is based on OpenCV and dlib.
 * @Description: If you find and bugs, please email me: fiery_heart@163.com
 */

#ifndef FACE_RECOGNITION
#define FACE_RECOGNITION

#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>
#include <dlib/image_processing/frontal_face_detector.h>
#include <dlib/gui_widgets.h>
#include <dlib/image_io.h>
#include <dlib/opencv.h>

class FaceRecognition {
    public:
        void SetFaceDetectionModel(std::string path) {
            face_detection_model_path = path;
        }
        void SetFaceAlignmentModel(std::string path) {
            face_alignment_model_path = path;
        }
        void SetFaceMeasurementModel(std::string path) {
            face_measurement_model_path = path;
        }
        void SetFaceRecognitionModel(std::string path) {
            face_recognition_model_path = path;
        }
        void SetCameraCapture(int number, int width, int height){
            capture = number;
            capture.set(CV_CAP_PROP_FRAME_WIDTH, width);
	        capture.set(CV_CAP_PROP_FRAME_HEIGHT, height);
        }
        dlib::matrix<dlib::bgr_pixel> MatToMatrix(cv::Mat frame) {
            dlib::matrix<dlib::bgr_pixel> img;
            dlib::assign_image(img, dlib::cv_image<dlib::bgr_pixel>(frame));
            return img;
        }
        void LaunchCamera() {
            if(!capture.isOpened()) {
                std::cout << "The camera is not open." << std::endl;
                return;
            }
            while(1) {
                cv::Mat src_frame, dst_frame;
                capture >> src_frame;
                cv::flip(src_frame, dst_frame, 1);
                cv::imshow("Frame: ", dst_frame);
                if(cv::waitKey(30) >= 0) break;
            }
        }
        cv::Mat GetCamreaFrame() {
            cv::Mat src_frame, dst_frame;
            capture >> src_frame;
            cv::flip(src_frame, dst_frame, 1);
            return dst_frame;
        }
        FaceRecognition() {
            
        }
    private:
        std::string face_detection_model_path;
        std::string face_alignment_model_path;
        std::string face_measurement_model_path;
        std::string face_recognition_model_path;
        cv::VideoCapture capture;
};
#endif