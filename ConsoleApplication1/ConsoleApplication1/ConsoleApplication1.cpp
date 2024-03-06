#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main() {
    // Initialize the camera
    VideoCapture cap(0); // Use the default camera (change if needed)

    if (!cap.isOpened()) {
        cerr << "Error: Could not open camera." << endl;
        return -1;
    }

    while (true) {
        Mat frame;
        cap >> frame; // Capture a frame from the camera

        // Convert the frame to grayscale
        Mat gray;
        cvtColor(frame, gray, COLOR_BGR2GRAY);

        // Apply Canny edge detection
        Mat edges;
        Canny(gray, edges, 50, 150);

        // Apply Hough Line Transform
        vector<Vec2f> lines;
        HoughLines(edges, lines, 1, CV_PI / 180, 150, 0, 0);

        // Draw the lines on the original frame
        for (size_t i = 0; i < lines.size(); ++i) {
            float rho = lines[i][0];
            float theta = lines[i][1];
            double a = cos(theta);
            double b = sin(theta);
            double x0 = a * rho;
            double y0 = b * rho;
            Point pt1(cvRound(x0 + 1000 * (-b)), cvRound(y0 + 1000 * (a)));
            Point pt2(cvRound(x0 - 1000 * (-b)), cvRound(y0 - 1000 * (a)));

  
            cout << pt1 << endl;
            line(frame, pt1, pt2, Scalar(0, 0, 120), 2); // Draw lines
        }

        // Display the result
        imshow("Edges and Lines", frame);

        // Press 'q' to exit
        if (waitKey(1) == 'q') {
            cout << "Exiting program" << endl;
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
    return 0;
}
