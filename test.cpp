#include "hwnd2Mat.h"
#include "DS_timer.h"
#include "DS_definitions.h"
#include <queue>

int main()
{
    Mat ui(40, 400, CV_8UC3, Scalar(0, 130, 0));
    putText(ui, "Press Esc to stop capturing", Point(30, 30), FONT_HERSHEY_COMPLEX, 0.7,
        Scalar(0, 0, 255), 1);
    Mat bgrImg;
    hwnd2Mat capDesktop(GetDesktopWindow());

    //VideoWriter writer;
    //int codec = VideoWriter::fourcc('X', 'V', 'I', 'D');
    //double fps = 10.0;
    //string filename = "./desktop_capture.avi";
    //writer.open(filename, codec, fps, capDesktop.image.size(), true);
    // check if we succeeded
    /*if (!writer.isOpened()) {
        cerr << "Could not open the output video file for write\n";
        return -1;
    }*/

    DS_timer timer(2);

    timer.setTimerName(0, (char *)"100frame capture overhead");

    queue<Mat> imgQueue;

    timer.onTimer(0);
    while (true)
    {
        capDesktop.read();
        cvtColor(capDesktop.image, bgrImg, COLOR_BGRA2BGR);

        //writer << bgrImg;
        imgQueue.push(capDesktop.image);
        
        //imshow("desktop capture", ui);
        
        int key = waitKey(2);

        if (key == 27)
            break;

        if (imgQueue.size() > 100) break;
    }
    timer.offTimer(0);

    cout << imgQueue.front().cols << " * " << imgQueue.front().rows << endl;

    timer.printTimer();
    timer.initTimers();
}