#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

int main(/* int argc, char** argv */)
{
   /* if( argc != 2)
    {
     cout <<" Usage: " << argv[0] << " ImageToLoadAndDisplay" << endl;
     return -1;
    }*/
	int camera = 0;

	cout << "Pick webcam source 0, 1, or 2, then press ENTER." << endl;
	cin >> camera;

	VideoCapture cap(camera);

 // if not success, exit program
 if (cap.isOpened() == false)  
 {
  cout << "Cannot open the video camera" << endl;
  cin.get(); //wait for any key press
  return -1;
 }

 
 while (true)
 {
  Mat frame;
  bool bSuccess = cap.read(frame); // read a new frame from video 

  //Breaking the while loop if the frames cannot be captured
  if (bSuccess == false) 
  {
   cout << "Video camera is disconnected" << endl;
   cin.get(); //Wait for any key press
   break;
  }
	
    Mat image;

	Mat block0, block1, block2, block3, block4, block5, block6, block7, block8, block9;
    Mat blocks [10] = {block0, block1, block2, block3, block4, block5, block6, block7, block8, block9};

	//string image_path = "D:\\JoeyFilterTest\\face.jpg";
	
 	string path0 = samples::findFile("0.jpg");
	string path1 = samples::findFile("1.jpg");
	string path2 = samples::findFile("2.jpg");
	string path3 = samples::findFile("3.jpg");
	string path4 = samples::findFile("4.jpg");
	string path5 = samples::findFile("5.jpg");
	string path6 = samples::findFile("6.jpg");
	string path7 = samples::findFile("7.jpg");
	string path8 = samples::findFile("8.jpg");
	string path9 = samples::findFile("9.jpg");
	string paths [10] = {path0, path1, path2, path3, path4, path5, path6, path7, path8, path9};
	
	//image = imread(image_path, IMREAD_COLOR);
 	image = frame;

	for(int i = 0; i < 10; i++)
	{
		blocks [i] = imread(paths [i], IMREAD_COLOR);
		if (blocks [i].empty())
		{
			cout << "block image " << i << " not available";
		};
	};

	int height = image.rows;
	int width = image.cols;
 
	for(int pixel_Y = 4; pixel_Y < (height - 10); pixel_Y += 10)
	{
		for(int pixel_X = 4; pixel_X < (width - 10); pixel_X += 10)
		{
		Vec3b intensity = image.at <Vec3b>(pixel_Y, pixel_X);
		int brightness = (intensity.val [0] + intensity.val [1] + intensity.val [2]) / 3;
		//	brightness = pow(brightness/255.0, .4) * 255.;
		brightness = 2.3 * brightness;
			
		Mat roi = image (Rect(pixel_X - 4, pixel_Y - 4, 10, 10));
			int chosenBlock;
			if ((brightness/25)-1 < 0)
			{
				chosenBlock = 0;
			}
			else if ((brightness/25)-1 > 9)
			{
				chosenBlock = 9;
			}
			else
			{
				chosenBlock = (brightness/25)-1;
			}

			blocks [chosenBlock].copyTo(roi);
			
		/*cout << "pixel at " << pixel_Y << ", " << pixel_X << " intensity is (" << static_cast<unsigned>(intensity.val [0])
		<< ", " << static_cast<unsigned>(intensity.val [1]) << ", " << static_cast<unsigned>(intensity.val [2])
		<< ") or " << brightness <<endl;*/
		}
	}


    //image = imread(argv[1], IMREAD_COLOR); // Read the file
    if( image.empty() ) // Check for invalid input
    {
        cout << "Could not open or find the image" << std::endl ;
        return -1;
    }
    namedWindow( "Display window", WINDOW_AUTOSIZE ); // Create a window for display.
    imshow( "Display window", image ); // Show our image inside it.
	//imwrite("D:\\JoeyFilterTest\\Filtered.jpg",image);
    if(waitKey(2) == 27) // Wait for a keystroke in the window
  {
	 break;
  }
 }
	
    return 0;
}
