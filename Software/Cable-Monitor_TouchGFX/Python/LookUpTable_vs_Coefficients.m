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
y = [1000 500 200 80 30  20  10];

d = [10 50 100];
s = [200 30 20];

a = ((s(1)^2) * (s(2) - s(3)) * d(1) - s(1) * ((s(2)^2) * d(2) - (s(3)^2) * d(3)) + s(2) * (s(2) * d(2) - s(3) * d(3)) * s(3)) / ((s(1)^2 - s(1) * (s(2) + s(3)) + s(2) * s(3)) * (s(2) - s(3)));

b = -(s(1)^2 * (s(2)^2 * (d(1) - d(2)) - s(3)^2 * (d(1) - d(3))) + s(2)^2 * s(3)^2 * (d(2) - d(3))) / ((s(1)^2 - s(1) * (s(2) + s(3)) + s(2) * s(3)) * (s(2) - s(3)));

c = (s(1) * (s(1) * (s(2) * (d(1) - d(2)) - s(3) * (d(1) - d(3))) + s(2) * s(3) * (d(2) - d(3))) * s(2) * s(3)) / ((s(1)^2 - s(1) * (s(2) + s(3)) + s(2) * s(3)) * (s(2) - s(3)));

%% Calculate the values of the Look-Up-Table
xi = 0:1:200;
yi = interp1(x,y,xi,'pchip');

d_ = 0:1:200;
s_ = a + b./d_ + c./(d_.^2);

% Plot samples and LUT for visual verification
plot(d_, s_, Color='red', LineWidth=2);
ylim([0 1000]);
hold on;
plot(xi,yi, LineWidth=2); grid;
title('Look-Up-Table vs Coefficient Approx');
xlabel('Distance in mm');
ylabel('Signal Strength');
legend('Function using coefficient approx', 'Function using Interpolation')

%% Round to integer if desired
%%lut = round(yi);

%% Write to a file
%%csvwrite('lut.csv', lut);
