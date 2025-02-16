#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cmath>

float A, B, C; //Winkel

const int size_ = 12;
const int width_ = 160;
const int height_ = 44;
const int depth_ = 60;

char screen[height_][width_];

float calcX(const int& i, const int& j, const int& k){
    return j * std::sin(A) * std::sin(B) * std::cos(C) - 
    k * std::cos(A) * std::sin(B) * std::cos(C) +
    j * std::cos(A) * std::sin(C) + 
    k * std::sin(A) * std::sin(C) + 
    i * std::cos(B) * std::cos(C);
}
float calcY(const int& i, const int& j, const int& k){
    return j * std::cos(A) * std::cos(C) + 
    k * std::sin(A) * std::cos(C) - 
    j * std::sin(A) * std::sin(B) * std::sin(C) +
    k * std::cos(A) * std::sin(B) * std::sin(C) - 
    i * std::cos(B) * std::sin(C);    
}
float calcZ(const int& i, const int& j, const int& k){
    return k * std::cos(A) * std::cos(B) - 
    j * std::sin(A) * std::cos(B) + 
    i * std::sin(B);
}

void clearBuffer(){
    for(int i = 0; i < height_; i++){
        for(int j = 0; j < width_; j++){
            screen[i][j] = ' '; 
        }
    }
}

void drawBuffer(){
    std::cout << "\033[H";
    for(int i = 0; i < height_; i++){
        for(int j = 0; j < width_; j++){
            putchar(screen[i][j]);
        }
    }
}

void calculateSurface(const float& xp_, const float& yp_, const float& zp_, int ch){
    float x = calcX(xp_, yp_, zp_);
    float y = calcY(xp_, yp_, zp_);
    float z = calcZ(xp_, yp_, zp_) + depth_;

    int xp = (int)(x/z * depth_ + width_/2); // projected point x
    int yp = (int)(y/z * depth_ + height_/2); // projected point y

    screen[yp][xp] = ch; //miserable way -> check if some conditions are fullfilled before putting the char
}

int main(){
    while(true){
        clearBuffer();
        for(float cubeX = -size_; cubeX < size_; cubeX += 0.6){
            for(float cubeY = -size_; cubeY < size_; cubeY += 0.6){
                calculateSurface(cubeX, cubeY, -size_, '@');
                calculateSurface(size_, cubeY, cubeX, '$');
                calculateSurface(-size_, cubeY, -cubeX, '+');
                calculateSurface(-cubeX, cubeY, size_, '#');
                calculateSurface(cubeX, -size_, -cubeY, ';');
                calculateSurface(cubeX, size_, cubeY, '~');
            }
        } 
        drawBuffer();

        A += 0.005;
        B += 0.005;
        usleep(1000);
	}
    return 0;
}
