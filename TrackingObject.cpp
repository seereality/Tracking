#include <stdio.h>
#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

int x_prev = 0; int y_prev = 0; int A_prev = 0; int delta_a = 0;

// Mouse Click function
void mouse_click(int Area)
{
    delta_a = A_prev - Area;
    A_prev = Area;
    //cout<<delta_a<<"\n";
    if(delta_a < -500)
    {
        system("xdotool click 1");
    }
}

void mousemove(int x_pos, int y_pos)
{
    
    string xcord; string ycord;

    stringstream sstr; stringstream sstr2;

    // Conversion to regular string happens here
    sstr<<5*x_pos;
    xcord = sstr.str();
    sstr2<<5*y_pos;
    ycord = sstr2.str();

    // Getting the Command string
    string command = "xdotool mousemove " + xcord + " " + ycord;

    // Converting to system() form
    const char *com = command.c_str();
    system(com);
}

void getCentroid(Mat &thresholded_image, Point &Centroid, int &Area)
{
    Moments m = moments(thresholded_image, true);
    
    double M10 = m.m10;
    
    double M01 = m.m01;
    
    double M00 = m.m00;
    Centroid.x  = int(M10/M00);
    Centroid.y  = int(M01/M00);
    Area        = int(M00);
}

void HSV_threshold(Mat &image, Mat &output_image_gray, int H_upper, int H_lower, int S_upper, int S_lower, int V_upper, int V_lower)
{
    Mat HSV;

    cvtColor(image, HSV, CV_RGB2HSV);

    int i, j;
        for(i=0; i<image.rows; i++)
        {
            for(j=0; j<image.cols; j++)
            {
                if((HSV.at<Vec3b>(i,j)[0] > H_lower)&&(HSV.at<Vec3b>(i,j)[0] < H_upper)&&(HSV.at<Vec3b>(i,j)[1]>S_lower)&&(HSV.at<Vec3b>(i,j)[1]<S_upper)&&(HSV.at<Vec3b>(i,j)[2]<V_upper)&&(HSV.at<Vec3b>(i,j)[2]>V_lower)) output_image_gray.at<uchar>(i,j) = 255;
                else output_image_gray.at<uchar>(i,j) = 0;
            }
        }
	imshow("Output Gray",output_image_gray);
}

Mat Canny_Filter(Mat &gray_image, int lower_thresh,int upper_thresh)
{
    Mat edges;

    blur(gray_image, edges, Size(3,3));

    Canny(edges, edges, lower_thresh, upper_thresh, 3);

    return edges;
}

int main(int argc, char** argv)
{

    int camera_number    = 0;   int Hue_lower_thresh = 31;//99;//0;
    int max_thresh       = 255; int Hue_upper_thresh = 147;//142;//7;
    int Sat_lower_thresh = 131;/*156;/*170;*/  int Sat_upper_thresh = 212;//251;//255;
    int Val_lower_thresh = 0;/*69;/*35;*/ int Val_upper_thresh = 169;//171;//216;
    Mat camera_frame; Mat displayed_frame; Mat gray_frame; //Mat thresh_frame;    
    namedWindow("camfeed");
    
    createTrackbar("Hue lower", "camfeed", &Hue_lower_thresh, max_thresh, NULL);
    createTrackbar("Hue upper", "camfeed", &Hue_upper_thresh, max_thresh, NULL);
    createTrackbar("Sat upper", "camfeed", &Sat_upper_thresh, max_thresh, NULL);
    createTrackbar("Sat lower", "camfeed", &Sat_lower_thresh, max_thresh, NULL);
    createTrackbar("Val upper", "camfeed", &Val_upper_thresh, max_thresh, NULL);
    createTrackbar("Val lower", "camfeed", &Val_lower_thresh, max_thresh, NULL);

    ///Camera setup
    VideoCapture camera;
    camera.open(camera_number);
    if(! camera.isOpened())
    {
        cerr<<"ERROR: COULD NOT ACCESS THE CAMERA!"<<endl;
        exit(1);
    }

    // Setting the camera resolution
    camera.set(CV_CAP_PROP_FRAME_WIDTH, 396);
    camera.set(CV_CAP_PROP_FRAME_HEIGHT, 216);

    
    while(true)
    {
        
        camera >> camera_frame;
        if(camera_frame.empty())
        {
            cerr<<"ERROR: COULD NOT GRAB A FRAME!"<<endl;
            exit(1);
        }

        flip(camera_frame, camera_frame, 1);

        Mat thresh_frame(Size(camera_frame.cols, camera_frame.rows), CV_8U);
        
        HSV_threshold(camera_frame, thresh_frame, Hue_upper_thresh, Hue_lower_thresh, Sat_upper_thresh, Sat_lower_thresh, Val_upper_thresh, Val_lower_thresh);
        medianBlur(thresh_frame, thresh_frame, 5); 
        Point Centroid; int Area;
        getCentroid(thresh_frame, Centroid, Area);

        imshow("camfeed", camera_frame);
        //cout<<"Area is:"<<Area<<endl;;
        
        if((Centroid.x<thresh_frame.cols)&&(Centroid.x>0)&&(Centroid.y>0)&&(Centroid.y<thresh_frame.rows))
        {
            if(Area > 100)
            {
                mousemove(Centroid.x, Centroid.y);
				//cout<<"Inn"<<endl;
            }
        }
        mouse_click(Area);
        //imshow("BLUE", bgr_planes[0]);
        //imshow("GREEN", bgr_planes[1]);
        //imshow("RED", bgr_planes[2]);

        // Listening for the user to press a key on the keyboard
        char keypress = waitKey(10);

        // If user presses 'c' stop program and save current frame to file
        if(keypress == 'c')
        {
            imwrite("capture.png", camera_frame);
            cout<<"Image captured"<<"Now exiting program";
            break;
        }
        if(keypress == 'a') cout<<Area<<"\n";
        
        if(keypress == 27)
        {
            break;
        }
    }

    return 0;
}
