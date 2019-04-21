/*
 * @Description: 程序main函数
 * @Author: fieryheart
 * @LastEditors: Please set LastEditors
 * @Date: 2019-04-03 21:07:46
 * @LastEditTime: 2019-04-21 19:41:12
 */
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "./src/FaceAlignment.h"
using namespace std;
using namespace cv;

void toTest();  // 测试
void toGetBoundingBox(); // 获取人脸边框
void toTrain(); // 训练模型
void toCamera(); // 获取电脑摄像头

int main()
{
    int flag = 4;
    if (flag == 0) {

        cout << "starting..." << endl;

    } else if (flag == 1) { // 测试集

        cout << "toTest()..." << endl;
        toTest();
    
    } else if (flag == 2) { // 训练模型
    
        cout << "toTrain()..." << endl;
        toTrain();
    
    } else if(flag == 3) { // 获取人脸边框
        
        cout << "toGetBoundingBox()..." << endl;
        toGetBoundingBox();

    } else if(flag == 4) { // 摄像头捕捉

        cout << "toCamera()..." << endl;
        toCamera();

    }
    return 0;
}

void toTest()
{
    vector<Mat_<uchar> > test_images;
    Mat image, image_temp;
    vector<BoundingBox> test_bounding_box;
    int test_img_num = 507;
    int initial_number = 20;
    int landmark_num = 29;
    ifstream fin;

    // for(int i = 0;i < test_img_num;i++){
    //     string image_name = "./data/testImages/";
    //     image_name = image_name + to_string(i+1) + ".jpg";
    //     Mat_<uchar> temp = imread(image_name,0);
    //     test_images.push_back(temp);
    // }

    image = imread("./data/testImages/test2.jpg", 0);
    resize(image, image_temp, Size(0, 0), 0.5, 0.5, INTER_NEAREST);

    // imshow("result",image_temp);
    // waitKey(0);
    // return;

    CascadeClassifier face_cascade;
    if(!face_cascade.load("./data/haarcascade_frontalface_alt_tree.xml")) {
        cout << "Loading cascade error" << endl;
    }

    vector<Rect> faceRects;
    face_cascade.detectMultiScale(
        image_temp,
        faceRects,
        1.1,
        2,
        0 | CV_HAAR_SCALE_IMAGE,
        Size(80, 80)
    );

    // fin.open("./data/boundingbox_test.txt");
    // for(int i = 0;i < test_img_num;i++){
    //     BoundingBox temp;
    //     fin>>temp.start_x>>temp.start_y>>temp.width>>temp.height;
    //     temp.centroid_x = temp.start_x + temp.width/2.0;
    //     temp.centroid_y = temp.start_y + temp.height/2.0; 
    //     test_bounding_box.push_back(temp);
    // }
    // fin.close(); 
    
    BoundingBox boundingBox_temp;
    boundingBox_temp.start_x = faceRects[0].x;
    boundingBox_temp.start_y = faceRects[0].y;
    boundingBox_temp.width = faceRects[0].width;
    boundingBox_temp.height = faceRects[0].height;
    boundingBox_temp.centroid_x = boundingBox_temp.start_x + boundingBox_temp.width / 2.0;
    boundingBox_temp.centroid_y = boundingBox_temp.start_y + boundingBox_temp.height / 2.0;

    ShapeRegressor regressor;
    regressor.Load("./data/model.txt");

    Mat_<double> current_shape = regressor.Predict(image_temp,boundingBox_temp,initial_number);
    Mat image_temp_1 = image_temp.clone();
    for(int i = 0;i < landmark_num;i++){
        circle(image_temp_1,Point2d(current_shape(i,0),current_shape(i,1)),3,Scalar(255,0,0),-1,8,0);
    }
    imshow("result",image_temp_1);
    waitKey(0);


    // while(true){
    //     int index = 1;
    //     cout<<"Input index:"<<endl;
    //     cin>>index;

    //     Mat_<double> current_shape = regressor.Predict(test_images[index],test_bounding_box[index],initial_number);
    //     Mat test_image_1 = test_images[index].clone();
    //     for(int i = 0;i < landmark_num;i++){
    //         circle(test_image_1,Point2d(current_shape(i,0),current_shape(i,1)),3,Scalar(255,0,0),-1,8,0);
    //     }
    //     imshow("result",test_image_1);
    //     waitKey(0);
    // }    
    return ;
}

/**
 * @description: 获取人脸框数据
 * @param {void} 
 * @return: 
 */
void toGetBoundingBox()
{
    CascadeClassifier face_cascade;
    if(!face_cascade.load("./data/haarcascade_frontalface_alt_tree.xml")) {
        cout << "Loading cascade error" << endl;
    }

    int trainingImgsNumber = 1345;
    string prePath = "./data/trainingImages/";
    vector<string> paths;
    ofstream boundingbox_ofs, boundingbox_is_ofs;

    for(int i = 0; i < trainingImgsNumber; ++i)
    {
        paths.push_back(prePath + to_string(i+1) + ".jpg");
    }

    if(paths.size() == 0) {
        cout << "No images" << endl;
        return;
    }

    boundingbox_ofs.open("./data/boundingbox.txt", std::ios::out | std::ios::trunc);
    boundingbox_is_ofs.open("./data/boundingbox_is.txt", std::ios::out | std::ios::trunc);

    if(!boundingbox_ofs.is_open() && !boundingbox_is_ofs.is_open()) {
        cout << "opening error" << endl;
        return;
    }

    for(int i = 0; i < paths.size(); ++i) {
        Mat srcImg, dstImg;
        
        srcImg = imread(paths[i], 0);

        if(srcImg.data) {
            vector<Rect> faceRects;
            face_cascade.detectMultiScale(
                srcImg,
                faceRects,
                1.1,
                2,
                0 | CV_HAAR_SCALE_IMAGE,
                Size(80, 80)
            );

            /*
            for(unsigned int j = 0; j < faceRects.size(); ++j) {
                // rectangle(
                //     srcImg,
                //     cvPoint(faceRects[i].x - faceRects[i].width/4, faceRects[i].y - faceRects[i].height/4),
                //     cvPoint(faceRects[i].x + faceRects[i].width/4*5, faceRects[i].y + faceRects[i].height/4*5),
                //     cvScalar(0, 255, 0),
                //     2, 8, 0);
                ofs << faceRects[j].x - faceRects[j].width/4 << " " << faceRects[j].y - faceRects[j].height/4 
                << " " << faceRects[j].x + faceRects[j].width/4*5 << " " << faceRects[j].y + faceRects[j].height/4*5 << endl;
            } 
            if(faceRects.size() == 0){
                notDetected.push_back(i);
            }
            */

            // resize(srcImg, dstImg, Size(), 1, 1, CV_INTER_AREA);
            // imshow("显示图像：", dstImg);

            if(faceRects.size() == 0) {
                boundingbox_ofs << "0 0 0 0" << endl;
                // cout << i+1 << endl;
            } else {
                boundingbox_ofs << faceRects[0].x << " " << faceRects[0].y << " " << faceRects[0].x + faceRects[0].width << " " << faceRects[0].y + faceRects[0].height << endl;
                boundingbox_is_ofs << i+1 << endl;           
            }

        } else {
            cout << "Loading image" << i+1 <<" error" << endl;
            break;
        }
    }

    boundingbox_ofs.close();
    boundingbox_is_ofs.close();
    // waitKey(0);
    return;
}

/**
 * @description: 训练模型
 * @param {type} 
 * @return: 
 */
void toTrain()
{
    int img_num = 1345;
    int candidate_pixel_num = 400;
    int fern_pixel_num = 5;
    int first_level_num = 10;
    int second_level_num = 500; 
    int landmark_num = 29;
    int initial_number = 20;
    int isFace[2000] = {0};
    vector<Mat_<uchar> > images, images_temp;
    vector<BoundingBox> bbox, bbox_temp; 
    
    cout<<"Read images..."<<endl;
    for(int i = 0;i < img_num;i++){
        string image_name = "./data/trainingImages/";
        image_name = image_name + to_string(i+1) + ".jpg";
        Mat_<uchar> temp = imread(image_name,0);
        images_temp.push_back(temp);
    }
    
    vector<Mat_<double> > ground_truth_shapes, ground_truth_shapes_temp;
    vector<BoundingBox> bounding_box, bounding_box_temp;
    ifstream fin;
    fin.open("./data/boundingbox.txt");
    for(int i = 0;i < img_num;i++){
        BoundingBox temp;
        fin >> temp.start_x >> temp.start_y >> temp.width >> temp.height;
        temp.centroid_x = temp.start_x + temp.width/2.0;
        temp.centroid_y = temp.start_y + temp.height/2.0; 
        bounding_box_temp.push_back(temp);
    }
    fin.close(); 

    fin.open("./data/keypoints.txt");
    for(int i = 0; i < img_num; i++) {
        Mat_<double> temp(landmark_num,2);
        for(int j = 0;j < landmark_num;j++){
            fin >> temp(j,0); 
        }
        for(int j = 0;j < landmark_num;j++){
            fin >> temp(j,1); 
        }
        ground_truth_shapes_temp.push_back(temp);
    }
    fin.close(); 
    
    fin.open("./data/boundingbox_is.txt");
    for(int i = 0; i < 1050; i++) {
        int temp;
        fin >> temp;
        isFace[temp-1] = 1;
    }
    fin.close();

    for(int i = 0; i < img_num; ++i) {
        if(isFace[i]) {
            images.push_back(images_temp[i]);
            ground_truth_shapes.push_back(ground_truth_shapes_temp[i]);
            bounding_box.push_back(bounding_box_temp[i]);
        }
    }

    ShapeRegressor regressor;
    regressor.Train(images,ground_truth_shapes,bounding_box,first_level_num,second_level_num,
                    candidate_pixel_num,fern_pixel_num,initial_number);
    regressor.Save("./data/model.txt");
    return;
}

void toCamera()
{
    //打开视频捕捉器
    VideoCapture capture(0);
    if(!capture.isOpened()){
        cout << "cannot open camera" << endl;
        return ;
    }

    // 设置分辨率
    capture.set(3, 320);
    capture.set(4, 240);

    int initial_number = 20;
    int landmark_num = 29;
    BoundingBox boundingBox_temp;
    CascadeClassifier face_cascade;
    if(!face_cascade.load("./data/haarcascade_frontalface_alt_tree.xml")) {
        cout << "Loading cascade error" << endl;
    }

    ShapeRegressor regressor;
    regressor.Load("./data/model_author.txt");

    TickMeter tm;

    while(true) {
        
        Mat frame, frame_gray, frame_flip, image_temp;
        
        tm.reset();
		tm.start();

        for(int i = 0; i < 100; ++i) {
            capture >> frame;

            cvtColor(frame, frame_gray, CV_RGB2GRAY);

            flip(frame_gray, frame_flip, 1);

            vector<Rect> faceRects;
            face_cascade.detectMultiScale(
                frame_flip,
                faceRects,
                1.1,
                2,
                0 | CV_HAAR_SCALE_IMAGE,
                Size(80, 80)
            );

            image_temp = frame_flip;
            // image_temp = frame;

    
            if(faceRects.size()) {
                boundingBox_temp.start_x = faceRects[0].x;
                boundingBox_temp.start_y = faceRects[0].y;
                boundingBox_temp.width = faceRects[0].width;
                boundingBox_temp.height = faceRects[0].height;
                boundingBox_temp.centroid_x = boundingBox_temp.start_x + boundingBox_temp.width / 2.0;
                boundingBox_temp.centroid_y = boundingBox_temp.start_y + boundingBox_temp.height / 2.0;

                
                Mat_<double> current_shape = regressor.Predict(frame_flip, boundingBox_temp, initial_number);
                
                image_temp = frame_flip.clone();
                
                for(int i = 0;i < landmark_num;i++){
                    circle(image_temp,Point2d(current_shape(i,0),current_shape(i,1)),3,Scalar(255,0,0),-1,8,0);
                }
                
                
            }
    
            imshow("result",image_temp);

            if(waitKey(1) == 27);
        }
        tm.stop();
        cout << 100 / tm.getTimeSec() << "fps" << endl;


    }
    capture.release();
    return;
}