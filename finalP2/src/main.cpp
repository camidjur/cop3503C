
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "Header.h"
#include "Pixels.h"
using namespace std;


void Load(string fileName, Header& header) {
	// creates file stream that will read binary
	ifstream file(fileName, ios_base::binary);

	// is file open?
	if (file.is_open()) {
		// reads in all the variables for a header
		file.read(&header.idLength, sizeof(header.idLength));
		file.read(&header.colorMapType, sizeof(header.colorMapType));
		file.read(&header.dataTypeCode, sizeof(header.dataTypeCode));
		file.read((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
		file.read((char*)&header.colorMapLength, sizeof(header.colorMapLength));
		file.read(&header.colorMapDepth, sizeof(header.colorMapDepth));
		file.read((char*)&header.xOrigin, sizeof(header.xOrigin));
		file.read((char*)&header.yOrigin, sizeof(header.yOrigin));
		file.read((char*)&header.width, sizeof(header.width));
		file.read((char*)&header.height, sizeof(header.height));
		file.read(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
		file.read(&header.imageDescriptor, sizeof(header.imageDescriptor));

		// uses the info passed in to get size of pixels 
		int numOfPixels = header.width * header.height;
		Pixels smallP;

		//reads in pixels 
		for (unsigned int i = 0; i < numOfPixels; i++) {
			file.read((char*)&smallP.blue, sizeof(smallP.blue));
			file.read((char*)&smallP.green, sizeof(smallP.green));
			file.read((char*)&smallP.red, sizeof(smallP.red));

			// saves pixels into header vector 
			header.pixels.push_back(smallP);
		}
	}
}
Header& Multiply(Header& top, Header& bottom) {
	
	float tempVal1;
	float tempVal2;

	for (unsigned int i = 0; i < top.pixels.size(); i++) {
		tempVal1 = top.pixels[i].blue / 255.0f;
		tempVal2 = bottom.pixels[i].blue / 255.0f;
		top.pixels[i].blue = (unsigned char)((tempVal1 * tempVal2 * 255.0f) + 0.5f);

		tempVal1 = top.pixels[i].green / 255.0f;
		tempVal2 = bottom.pixels[i].green / 255.0f;
		top.pixels[i].green = (unsigned char)((tempVal1 * tempVal2 * 255.0f) + 0.5f);;

		tempVal1 = top.pixels[i].red / 255.0f;
		tempVal2 = bottom.pixels[i].red / 255.0f;
		top.pixels[i].red = (unsigned char)((tempVal1 * tempVal2 * 255.0f) + 0.5f);
	}

	return top;
}

char SubtractTheValues(float val1, float val2) {
	float temp = (val2 - val1);
	if (temp > 255) {
		return 255;
	}
	else if (temp < 0) {
		return 0;
	}
	else {
		return temp + 0.5f;
	}
}

Header& Subtract(Header& top, Header& bottom) {

	float temp1;
	float temp2;

	for (unsigned int i = 0; i < bottom.pixels.size(); i++) {

		temp1 = top.pixels[i].blue;
		temp2 = bottom.pixels[i].blue;
		top.pixels[i].blue = SubtractTheValues(temp1, temp2);

		temp1 = top.pixels[i].green;
		temp2 = bottom.pixels[i].green;
		top.pixels[i].green = SubtractTheValues(temp1, temp2);

		temp1 = top.pixels[i].red;
		temp2 = bottom.pixels[i].red;
		top.pixels[i].red = SubtractTheValues(temp1, temp2);
	}
	return top;
}

char ScreenTheValues(float val1, float val2) {
	val1 = 1 - (val1 / 255.0f);
	val2 = 1 - (val2 / 255.0f);
	float valToR;
	valToR = (1 - val1 * val2) * 255.0f;
	return valToR + 0.5f;
}

Header& Screen(Header& top, Header& bottom) {
	// C = 1 - (1 - A) * (1 - B)

	float temp1;
	float temp2;
	for (unsigned int i = 0; i < top.pixels.size(); i++) {
		temp1 = top.pixels[i].blue;
		temp2 = bottom.pixels[i].blue;
		top.pixels[i].blue = ScreenTheValues(temp1, temp2);
		
		temp1 = top.pixels[i].green;
		temp2 = bottom.pixels[i].green;
		top.pixels[i].green = ScreenTheValues(temp1, temp2);

		temp1 = top.pixels[i].red;
		temp2 = bottom.pixels[i].red;
		top.pixels[i].red = ScreenTheValues(temp1, temp2);
	}
	return top;
}
char OverlayTheValues(float val1, float val2) {
	val1 = val1/255.0f;
	val2 = val2/255.0f;
	if (val2 > 0.5) {
		return ((1 - (2 * (1 - val1) * (1 - val2))) * 255.0f) + 0.5f;
	}
	else {
		return (2 * (val1) * (val2) * 255.0f) + 0.5f;
	}
}

Header& Overlay(Header& top, Header& bottom) {
	// if B <= 0.5 --> C = 2 * A * B
	// if B > 0.5 --> C = 1 - 2 * (1 - A) * ( 1 - B)

	float temp1;
	float temp2;
	for (unsigned int i = 0; i < top.pixels.size(); i++) {
		temp1 = top.pixels[i].blue;
		temp2 = bottom.pixels[i].blue;
		top.pixels[i].blue = OverlayTheValues(temp1, temp2);

		temp1 = top.pixels[i].green;
		temp2 = bottom.pixels[i].green;
		top.pixels[i].green = OverlayTheValues(temp1, temp2);

		temp1 = top.pixels[i].red;
		temp2 = bottom.pixels[i].red;
		top.pixels[i].red = OverlayTheValues(temp1, temp2);
	}
	return top;
}

void Write(string outFileName, Header& header, int num) {
	ofstream outFile(outFileName, ios_base::binary);

	outFile.write(&header.idLength, sizeof(header.idLength));
	outFile.write(&header.colorMapType, sizeof(header.colorMapType));
	outFile.write(&header.dataTypeCode, sizeof(header.dataTypeCode));
	outFile.write((char*)&header.colorMapOrigin, sizeof(header.colorMapOrigin));
	outFile.write((char*)&header.colorMapLength, sizeof(header.colorMapLength));
	outFile.write(&header.colorMapDepth, sizeof(header.colorMapDepth));
	outFile.write((char*)&header.xOrigin, sizeof(header.xOrigin));
	outFile.write((char*)&header.yOrigin, sizeof(header.yOrigin));
	outFile.write((char*)&header.width, sizeof(header.width));
	outFile.write((char*)&header.height, sizeof(header.height));
	outFile.write(&header.bitsPerPixel, sizeof(header.bitsPerPixel));
	outFile.write(&header.imageDescriptor, sizeof(header.imageDescriptor));

	int numOfPixels = header.width * header.height;
	if (num == 0) {
		for (unsigned int i = 0; i < numOfPixels; i++) {
			outFile.write((char*)&header.pixels[i].blue, sizeof(header.pixels[i].blue));
			outFile.write((char*)&header.pixels[i].green, sizeof(header.pixels[i].green));
			outFile.write((char*)&header.pixels[i].red, sizeof(header.pixels[i].red));
		}
	}
	if (num == 1) {
		for (int i = (numOfPixels - 1); i >= 0; i--) {
			outFile.write((char*)&header.pixels[i].blue, sizeof(header.pixels[i].blue));
			outFile.write((char*)&header.pixels[i].green, sizeof(header.pixels[i].green));
			outFile.write((char*)&header.pixels[i].red, sizeof(header.pixels[i].red));
		}
	}
	

}

bool Test(string fileName1, string fileName2) {
	Header header1;
	Header header2;

	Load(fileName1, header1);
	Load(fileName2, header2);

	for (unsigned int i = 0; i < header1.pixels.size(); i++) {
		if (!(header1.pixels[i].blue == header2.pixels[i].blue)) {
			return false;
		}

		if (!(header1.pixels[i].green == header2.pixels[i].green)) {
			return false;
		}

		if (!(header1.pixels[i].red == header2.pixels[i].red)) {
			return false;
		}
	}
	return true;
}

int main()
{
	Header top;
	Header bottom;
	Header bottom2;
	Header car;
	Header task10;

	// Task 1 - multiply layer1.tga, pattern1.tga
	
	Load("input/layer1.tga", top);
	Load("input/pattern1.tga", bottom);

	Write("output/part1.tga", Multiply(top, bottom), 0);
	top.pixels.clear();
	bottom.pixels.clear();

	// test
	if (Test("examples/EXAMPLE_part1.tga", "output/part1.tga")) {
		cout << "test 1 sucessful" << endl;
	}
	else {
		cout << "test 1 failed" << endl;
	}

	// Task 2 - substract layer2.tga from car.tga
	
	Load("input/layer2.tga", top);
	Load("input/car.tga", bottom);

	Write("output/part2.tga", Subtract(top, bottom), 0);
	top.pixels.clear();
	bottom.pixels.clear();

	// test 
	if (Test("examples/EXAMPLE_part2.tga", "output/part2.tga")) {
		cout << "test 2 successful" << endl;
	}
	else {
		cout << "test 2 failed" << endl;
	}

	// Task 3 - multiply layer1.tga and pattern2.tga
	//then combine it with text.tga through the Screen process
	
	Load("input/text.tga", top);
	Load("input/layer1.tga", bottom);
	Load("input/pattern2.tga", bottom2);

	Write("output/part3.tga", Screen(top, Multiply(bottom, bottom2)), 0);
	top.pixels.clear();
	bottom.pixels.clear();
	bottom2.pixels.clear();

	// test 
	if (Test("example/EXAMPLE_part3.tga", "output/part3.tga")) {
		cout << "test 3 successful" << endl;
	}
	else {
		cout << "test 3 failed" << endl;
	}

	// Task 4 - multiply layer2.tga and circles.tga
	// subtract pattern2.tga from whatever that result is 

	Load("input/layer2.tga", top);
	Load("input/circles.tga", bottom);


	Write("input/temp.tga", Multiply(top, bottom), 0);
	top.pixels.clear();
	bottom.pixels.clear();

	Load("input/pattern2.tga", top);
	Load("input/temp.tga", bottom);

	Write("output/part4.tga", Subtract(top, bottom), 0);
	top.pixels.clear();
	bottom.pixels.clear();

	// test 
	if (Test("example/EXAMPLE_part4.tga", "output/part4.tga")) {
		cout << "test 4 successful" << endl;
	}
	else {
		cout << "test 4 failed" << endl;
	}

	// Task 5 - Overlay layer1.tga and pattern1.tga
	Load("input/layer1.tga", top);
	Load("input/pattern1.tga", bottom);

	Write("output/part5.tga", Overlay(top, bottom), 0);
	top.pixels.clear();
	bottom.pixels.clear();

	// test 
	if (Test("example/EXAMPLE_part5.tga", "output/part5.tga")) {
		cout << "test 5 successful" << endl;
	}
	else {
		cout << "test 5 failed" << endl;
	}

	// Task 6 - add 200 to green
	Load("input/car.tga", car);

	float temp;
	for (unsigned int i = 0; i < car.pixels.size(); i++) {
		temp = car.pixels[i].green + 200 + 0.5f;
		if (temp > 255) {
			temp = 255;
		}
		car.pixels[i].green = (unsigned char)temp;
	}
	Write("output/part6.tga", car, 0);
	car.pixels.clear();

	// test 
	if (Test("example/EXAMPLE_part6.tga", "output/part6.tga")) {
		cout << "test 6 successful" << endl;
	}
	else {
		cout << "test 6 failed" << endl;
	}

	// Task 7 - multiply red by 4 and blue by 0

	Load("input/car.tga", car);

	for (unsigned int i = 0; i < car.pixels.size(); i++) {
		car.pixels[i].red *= 4 / 255;
		car.pixels[i].blue = 0;
	}

	Write("output/part7.tga", car, 0);
	car.pixels.clear();

	// test 
	if (Test("example/EXAMPLE_part7.tga", "output/part7.tga")) {
		cout << "test 7 successful" << endl;
	}
	else {
		cout << "test 7 failed" << endl;
	}

	// Task 8 - make three different files, all red, all green, all blue

	// red image
	Load("input/car.tga", car);

	for (unsigned int i = 0; i < car.pixels.size(); i++) {
		car.pixels[i].blue = car.pixels[i].red;
		car.pixels[i].green = car.pixels[i].red;
	}
	Write("output/part8_r.tga", car, 0);
	car.pixels.clear();

	// test 
	if (Test("example/EXAMPLE_part8_r.tga", "output/part8_r.tga")) {
		cout << "test 8r successful" << endl;
	}
	else {
		cout << "test 8r failed" << endl;
	}

	// green image
	Load("input/car.tga", car);

	for (unsigned int i = 0; i < car.pixels.size(); i++) {
		car.pixels[i].blue = car.pixels[i].green;
		car.pixels[i].red = car.pixels[i].green;
	}
	Write("output/part8_g.tga", car, 0);
	car.pixels.clear();

	// test 
	if (Test("example/EXAMPLE_part8_g.tga", "output/part8_g.tga")) {
		cout << "test 8g successful" << endl;
	}
	else {
		cout << "test 8g failed" << endl;
	}

	// blue image
	Load("input/car.tga", car);

	for (unsigned int i = 0; i < car.pixels.size(); i++) {
		car.pixels[i].green = car.pixels[i].blue;
		car.pixels[i].red = car.pixels[i].blue;
	}
	Write("output/part8_b.tga", car, 0);
	car.pixels.clear();

	// test 
	if (Test("example/EXAMPLE_part8_b.tga", "output/part8_b.tga")) {
		cout << "test 8b successful" << endl;
	}
	else {
		cout << "test 8b failed" << endl;
	}

	// Task 9 - combine layer_red.tga, layer_green.tga, and layer_blue.tga

	Header redLayer;
	Header greenLayer;
	Header blueLayer;

	Load("input/layer_red.tga", redLayer);
	Load("input/layer_green.tga", greenLayer);
	Load("input/layer_blue.tga", blueLayer);

	for (unsigned int i = 0; i < redLayer.pixels.size(); i++) {
		redLayer.pixels[i].green = greenLayer.pixels[i].green;
		redLayer.pixels[i].blue = blueLayer.pixels[i].blue;
	}

	Write("output/part9.tga", redLayer, 0);

	// test 
	if (Test("example/EXAMPLE_part9.tga", "output/part9.tga")) {
		cout << "test 9 successful" << endl;
	}
	else {
		cout << "test 9 failed" << endl;
	}

	// Task 10 - rotate the image in text2.tga

	Load("input/text2.tga", task10);

	Write("output/part10.tga", task10, 1);

	// test 
	if (Test("example/EXAMPLE_part10.tga", "output/part10.tga")) {
		cout << "test 10 successful" << endl;
	}
	else {
		cout << "test 10 failed" << endl;
	}
};

