#include <iostream>
#include <string>
#include <cstdio>
#include <cmath>
#include <unistd.h>

float A, B, C;

const int width_ = 160, height_ = 44, depth_ = 60;
const int heart_size = 12;
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

void drawHeart(const float& x_, const float& y_, const float& z_, int ch){
    float x = calcX(x_, y_, z_);
    float y = calcY(x_, y_, z_);
    float z = calcZ(x_, y_, z_) + depth_;
    
    int dx = x - (int)width_/2;
    int dy = y - (int)height_/2;

    int xp = (int)(x/z * depth_ + width_ / 2);
    int yp = (int)(y/z * depth_ + height_ / 2);
    
    if(yp < 0)
        yp = 0;
    screen[yp][xp] = ch;
}

int main(){
    while(true){
        clearBuffer();
        for(float y_ = -heart_size; y_ < heart_size; y_+=0.1){
            for(float x_ = -heart_size; x_ < heart_size; x_+=0.1){
                if(std::pow((x_*x_ + y_*y_ - 1),3)  < std::abs(x_*x_*y_*y_*y_) + 100){     
                    drawHeart(y_, x_, -heart_size, '#');
                    //drawHeart(y_, x_, 0, '*');
                    //drawHeart(y_, x_, heart_size, '@');
                    //if(100 - x_*x_ - y_*y_ > 0){
                    //    drawHeart(y_, x_, std::sqrt(100 - x_*x_ - y_*y_), '.');
                    //    drawHeart(y_, x_, -std::sqrt(100 - x_*x_ - y_*y_), '*');
                    //}
                }
            }
        }
        drawBuffer();
        A += 0.05;
        B += 0.05;
        usleep(20000);
    }

    return 0;
}
