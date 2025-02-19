#include <iostream>
#include <array>
#include <unistd.h>
#include <cstring>
#include <cmath>

float A, B, C;

const int width_ = 160, height_ = 44, depth_ = 60;
const int size_ = 12;
std::array<std::array<char, width_>, height_> buffer;

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
            buffer[i][j] = ' ';
        }
    }
}

void drawBuffer(){
    std::cout << "\033[H";
    for(int i = 0; i < height_; i++){
        for(int j = 0; j < width_; j++){
            putchar(buffer[i][j]);
        }
    }
}

void calculateSurface(float x_, float y_, float z_, int ch){
    float x = calcX(x_, y_, z_);
    float y = calcY(x_, y_, z_);
    float z = calcZ(x_, y_, z_) + depth_;

    int xp = (int)(x / z * depth_ + width_/2);
    int yp = (int)(y / z * depth_ + height_/2);

    //std::cout << xp << " " << yp << " " << z << std::endl;
    buffer[yp][xp] = ch;
}

int main(){
    while(true){
        clearBuffer();
        for(float cubeX = -size_; cubeX < size_; cubeX += 0.6){
            for(float cubeY = -size_; cubeY < size_; cubeY += 0.6){
                if(cubeX*cubeX + cubeY*cubeY - 100 < 10)
                    calculateSurface(-cubeX, -cubeY, -size_, '#');
            }
        }
        drawBuffer();
        A += 0.005;
        B += 0.005;
        usleep(2000);
    }

    return 0;
}
