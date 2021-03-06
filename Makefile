CFLAGS = -I/usr/local/include/opencv -I/usr/local/include /usr/local/lib/libopencv_calib3d.so /usr/local/lib/libopencv_contrib.so /usr/local/lib/libopencv_core.so /usr/local/lib/libopencv_features2d.so /usr/local/lib/libopencv_flann.so /usr/local/lib/libopencv_gpu.so /usr/local/lib/libopencv_highgui.so /usr/local/lib/libopencv_imgproc.so /usr/local/lib/libopencv_legacy.so /usr/local/lib/libopencv_ml.so /usr/local/lib/libopencv_nonfree.so /usr/local/lib/libopencv_objdetect.so /usr/local/lib/libopencv_ocl.so /usr/local/lib/libopencv_photo.so /usr/local/lib/libopencv_stitching.so /usr/local/lib/libopencv_superres.so /usr/local/lib/libopencv_ts.a /usr/local/lib/libopencv_video.so /usr/local/lib/libopencv_videostab.so -lrt -lpthread -lm -ldl
CFLAGS = `pkg-config --cflags --libs opencv`
CC = g++


all: reco thresholding eigenfaces fisherfaces

reco: reco.cpp
	$(CC) reco.cpp -fopenmp -o recognition $(CFLAGS)

eigenfaces: eigenFacesRecognizer.cpp
	$(CC) eigenFacesRecognizer.cpp -fopenmp -o EigenFaces $(CFLAGS)

fisherfaces: fisherFacesRecognizer.cpp
	$(CC) fisherFacesRecognizer.cpp -fopenmp -o FisherFaces $(CFLAGS)

thresholding: thresholdRecognition.cpp
	$(CC) thresholdRecognition.cpp -fopenmp -o RecognitionThresholding $(CFLAGS)
	
video: faceRecoVideo.cpp
	$(CC) faceRecoVideo.cpp -o videoRecognition $(CFLAGS)
	
clean: recognition
	rm -rf recognition videoRecognition RecognitionThresholding EigenFaces
