#include "opencv2/core/core.hpp"
#include "opencv2/contrib/contrib.hpp"
#include "opencv2/highgui/highgui.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <ostream>
#include <string>
using namespace cv;
using namespace std;

namespace Color {
    enum Code {
	FG_RED      = 31,
        FG_GREEN    = 32,
        FG_BLUE     = 34,
        FG_DEFAULT  = 39,
        BG_RED      = 41,
        BG_GREEN    = 42,
        BG_BLUE     = 44,
        BG_DEFAULT  = 49
    };
    class Modifier {
        Code code;
        public:
               Modifier(Code pCode) : code(pCode) {}
    	       friend std::ostream&
	       operator<<(std::ostream& os, const Modifier& mod) {
               return os << "\033[" << mod.code << "m";
    	       }
	};
}


static void read_csv(const string& filename, vector<Mat>& images, vector<int>& labels, char separator = ';') {
    std::ifstream file(filename.c_str(), ifstream::in);
    if (!file) {
        string error_message = "No valid input file was given, please check the given filename.";
        CV_Error(CV_StsBadArg, error_message);
    }
    string line, path, classlabel;
    while (getline(file, line)) {
        stringstream liness(line);
        getline(liness, path, separator);
        getline(liness, classlabel);
        if(!path.empty() && !classlabel.empty()) {
            images.push_back(imread(path, 0));
            labels.push_back(atoi(classlabel.c_str()));
        }
    }
}

int main(int argc, const char *argv[]) {
    // Check for valid command line arguments, print usage
    // if no arguments were given.
    if (argc < 3) {
        cout << "usage: " << argv[0] << " <csvTraining.ext> <csvTesting.ext> " << endl;
        exit(1);
    }

    // Get the path to your Training CSV.
    string fn_csv = string(argv[1]);
	// Get the path to your Testing CSV .
    string fn_csv_test = string(argv[2]);
    // These vectors hold the images and corresponding labels.
    vector<Mat> images, imagesTesting;
    vector<int> labels, labelsTesting;
    // Read in the data. This can fail if no valid
    // input filename is given.
	cout << "Reading Images" << endl;
    try {
        read_csv(fn_csv, images, labels);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
	try {
        read_csv(fn_csv_test, imagesTesting, labelsTesting);
    } catch (cv::Exception& e) {
        cerr << "Error opening file \"" << fn_csv_test << "\". Reason: " << e.msg << endl;
        // nothing more we can do
        exit(1);
    }
    // Quit if there are not enough images for this demo.
    if(images.size() <= 1) {
        string error_message = "This demo needs at least 2 images to work. Please add more images to your data set!";
        CV_Error(CV_StsError, error_message);
    }
    // Get the height from the first image. We'll need this
    // later in code to reshape the images to their original
    // size:
    int height = images[0].rows;
//	std::string::size_type sz;     // alias of size_t
    double threshold = 50;
    if (argc == 4)
    {
    	threshold = atof(argv[3]);//std::stod(argv[3], &sz);
    }
	
    // The following lines create an LBPH model for
    // face recognition and train it with the images and
    // labels read from the given CSV file.
    //
    // The LBPHFaceRecognizer uses Extended Local Binary Patterns
    // (it's probably configurable with other operators at a later
    // point), and has the following default values
    //
    //      radius = 1
    //      neighbors = 8
    //      grid_x = 8
    //      grid_y = 8
    //
    // So if you want a LBPH FaceRecognizer using a radius of
    // 2 and 16 neighbors, call the factory method with:
    //
    //      cv::createLBPHFaceRecognizer(2, 16);
    //
    // And if you want a threshold (e.g. 123.0) call it with its default values:
    //
    //      cv::createLBPHFaceRecognizer(1,8,8,8,123.0)
    //
	
	double oldAcc =0, newAcc = 1, change = 3;
		// Training Stage
	cout << "Training The Recognizer with "<<images.size()<<" images \nIt may take some time" << endl;
	Ptr<FaceRecognizer> model = createLBPHFaceRecognizer();
	model->train(images, labels);
	
	while (abs(newAcc - oldAcc) > 0.3)
	{
		// Setting Threshold 
		model->set("threshold",threshold);
	
	
		// Testing Stage
		int mispredicted = 0;
		int unpredicted = 0;
		int predictedLabel = 0;
		double confidence = 0;
		cout << "Start testing " << labelsTesting.size() << " images one by one with threshold = "<< threshold << endl;
		for (int i=0; i<labelsTesting.size();i++)
		{
			//predictedLabel = model->predict(imagesTesting[i]);
			//
			// To get the confidence of a prediction call the model with:
			//
			//      int predictedLabel = -1;
			//      double confidence = 0.0;
			model->predict(imagesTesting[i], predictedLabel, confidence);
			//
			if (predictedLabel == -1)
			{
				unpredicted++;
				confidence = -1.0;
			}
			if (predictedLabel != labelsTesting[i] && predictedLabel != -1)
			{
				mispredicted++;
			}
			string result_message = format("Image : %03d   Predicted class = %02d / Actual class = %02d / with Confidence %02.3f.", i,predictedLabel,labelsTesting[i], confidence);
			cout << result_message << endl;
		}
		cout << "Unrecognized : " << unpredicted << endl; cout << "Mispredicted : " << mispredicted << endl; 
		double accuracy = double (labelsTesting.size() - unpredicted);
		accuracy = accuracy - mispredicted;
		accuracy = accuracy / (1.0*labelsTesting.size());
		accuracy = accuracy * 100.00;
		//(((labelsTesting.size()-(unpredicted+mispredicted))/labelsTesting.size()) * 100.0); 
		string acc = format("Number of Test Subjects is : %d\tNumber of Test Images is : %d \nAccuracy is %.3f %%", (labelsTesting[labelsTesting.size()-1] + 1),labelsTesting.size(),accuracy); 
		// Sometimes you'll need to get/set internal model data,
		Color::Modifier red(Color::FG_RED);
		Color::Modifier green(Color::FG_GREEN);
		Color::Modifier blue(Color::FG_BLUE);
		Color::Modifier def(Color::FG_DEFAULT);
		cout << green << acc << def << endl;
		oldAcc = newAcc;
		newAcc = accuracy;
		if (unpredicted >= mispredicted)
			threshold = threshold + change;
		else
			threshold = threshold - change;
	}
	    // which isn't exposed by the public cv::FaceRecognizer.
    // Since each cv::FaceRecognizer is derived from a
    // cv::Algorithm, you can query the data.
    //
    // First we'll use it to set the threshold of the FaceRecognizer
    // to 0.0 without retraining the model. This can be useful if
    // you are evaluating the model:
    //
    //model->set("threshold",25);
     // Now the threshold of this model is set to 0.0. A prediction
    // now returns -1, as it's impossible to have a distance below
    // it
    //predictedLabel = model->predict(testSample);
    //cout << "Predicted class = " << predictedLabel << endl;
	
	
	
    // Show some informations about the model, as there's no cool
    // Model data to display as in Eigenfaces/Fisherfaces.
    // Due to efficiency reasons the LBP images are not stored
    // within the model:
    cout << "Model Information:" << endl;
    string model_info = format("\tLBPH(radius=%i, neighbors=%i, grid_x=%i, grid_y=%i, threshold=%.2f)",
            model->getInt("radius"),
            model->getInt("neighbors"),
            model->getInt("grid_x"),
            model->getInt("grid_y"),
            model->getDouble("threshold"));
    cout << model_info << endl;
    // We could get the histograms for example:
    //vector<Mat> histograms = model->getMatVector("histograms");
    // But should I really visualize it? Probably the length is interesting:
    //cout << "Size of the histograms: " << histograms[0].total() << endl;
    return 0;
}
