%% Calculate the induced voltage of a magnetic field
%  into an inductor coil with ferrite core
%  Rough estimation for an *unshielded* inductor
%  (c) hhrt@zhaw.ch 13.02.2020
clc; clear; close all;
format compact; format short eng;
% Known values
B0 = 1e-5;              % Magnetic field in air (from simulation)
f = 50;                 % Frequency of mains
d = 5e-3;               % Diameter of coil (datasheet)
l = 3e-3;               % Length of coil (datasheet)
L = 10e-3;              % Inductance of coil (datasheet)
ur = 300;               % Relative permeability of ferrite (estimation)
% Calculation
u0 = 1.257e-6;          % Permeability of vacuum
A = pi*(d/2)^2;         % Cross section of coil
Br = B0*ur;             % Field in the ferrite body is stronger than in air
N = sqrt(L*l/(u0*ur*A)) % Number of turns of the coil
% The above formula is only correct for long air coils.
% It should be fine as an rough approximation.
% Check if the calculated N is plausible.
% Result
U = N*2*pi*f*A*Br       % Induced voltage in the coil


