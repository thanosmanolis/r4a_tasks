#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

using namespace cv;
using namespace std;

static const string OPENCV_WINDOW = "Image window";

static int lowThreshold = 0;
static const int ratio = 3;
static const int kernel_size = 3;

class EdgeDetector
{
    ros::NodeHandle nh_;
    image_transport::ImageTransport it_;
    image_transport::Subscriber image_sub_;
    image_transport::Publisher image_pub_;

    Mat src, src_gray;
    Mat dst, detected_edges;

    float count_;

public:
    EdgeDetector()
    : it_(nh_)
    {
        // Subscrive to input video feed and publish output video feed
        image_sub_ = it_.subscribe("/camera/depth/image_raw", 1,
            &EdgeDetector::imageCb, this);
    }

    ~EdgeDetector()
    {
        destroyWindow(OPENCV_WINDOW);
    }

    void imageCb(const sensor_msgs::ImageConstPtr& msg)
    {
        cv_bridge::CvImagePtr ptr;
        try
        {
            ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::TYPE_32FC1);
        }
        catch (cv_bridge::Exception& e)
        {
            ROS_ERROR("cv_bridge exception: %s", e.what());
            return;
        }

        dst.create(ptr->image.size(), ptr->image.type()); 

        // Depth -> CV_8U
        ptr->image.convertTo(src, CV_8U);

        namedWindow(OPENCV_WINDOW);   
        
        blur(src, detected_edges, Size(3,3));
        Canny(detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size);
        dst = Scalar::all(0);
        ptr->image.copyTo(dst, detected_edges);
        
        // Output modified video stream
        imshow(OPENCV_WINDOW, dst);
        waitKey(3);
        
        count_ = 0;
        for(int i = 0; i < dst.rows; ++i)
            for(int j = 0; j < dst.cols; j++)
                if (dst.at<float>(i,j) != 0)
                    ++count_;

        count_ = 100 * ((count_)/((dst.rows) * (dst.cols)));

        ROS_INFO("[count_] %.2f%%", count_);
        
    }
};

int main(int argc, char** argv)
{
    ros::init(argc, argv, "edge_detector");
    EdgeDetector ic;
    ros::spin();
    return 0;
}