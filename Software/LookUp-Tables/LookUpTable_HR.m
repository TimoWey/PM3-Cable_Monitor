%% Calculate a Look-Up-Table from sample points
% and store it in a csv file for later use in a C array
%
% In the C file the values can be imported into an array as follows:
% const int32_t LUT[] = {
%     #include "lut.csv"
% };  // The array is initialized with the values stored in the csv file.
% 
% (c) hhrt@zhaw.ch 24.07.2020
clc; clear; close all;

%% Enter the sample points
x = [   0   5  10 20 50 100 200];
y = [1130 1095 920 700 655  553  550];

%% Calculate the values of the Look-Up-Table
xi = 0:1:200;
yi = interp1(x,y,xi,'pchip');
x_ = 0:1:1420;
a = 0.050944;
b = -9.68167;
c = 1011.72;
f = a.*x_.^2+b.*x_+c;

% Plot samples and LUT for visual verification
plot(x,y,'o', xi,yi); grid;
hold on;
plot(f, x_);

xlabel('Distance in mm');
ylabel('Signal Strength from FFT');
title('Look-Up-Table');

%% Round to integer if desired
lut = round(yi);

%% Write to a file
csvwrite('lut.csv', lut);
