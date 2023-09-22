%% Bandpass filtering in time and frequency domains
%  (c) hhrt@zhaw.ch 13.05.2020
clc; clear; close all;
format compact; format short;
scrsz   = get(0,'ScreenSize');
figure('name', 'Bandpass Filtering in Time and Frequency Domains', ...
    'Position',[10,10,scrsz(3)-20,scrsz(4)-100]);

%% Parameters
Anoise = 0.5;             % Noise amplitude relativ to signal amplitude
fsignal = 50;           % Signal frequency
Nperiods = 10;          % Number of periods in input signal
N = 128;                % Number of samples
Nfir = 63;              % Filter order for FIR filter
Niir = 2;               % Filter order for IIR filter
Nfft = N;               % Length of the fast fourier transform

% Derived parameters
fs = N/Nperiods*fsignal;        % Sampling frequency
Wn = [0.9, 1.1]*fsignal/(fs/2); % Bandpass frequencies, relativ to fs/2

%% Noisy input signal
t = (0:N-1)/fs;         % Time vector
x = cos(2*pi*fsignal*t);    % Input signal without noise
x = x + Anoise*randn(1,N);  % Input signal with added noise

% Plot input signal
subplot(311);
plot(t,x,'o-k');
title('Input Signal');
grid;
xlabel('time / s');

%% Time domain filtering
try pkg load signal; catch ; end    % For compatibility with Octave
% FIR filter
Bfir = fir1(Nfir, Wn);
yfir = filter(Bfir,1,x);

% IIR filter
[Biir, Aiir] = butter(Niir, Wn);
yiir = filter(Biir,Aiir,x);

% Plot filter outputs
subplot(312);
plot(t,yfir,'s-b', t,yiir,'d-r');
title('Time Domain Filtering');
grid;
xlabel('time / s');
legend('FIR filter output', 'IIR filter output', 'Location', 'NorthWest');

%% Frequency domain filtering
% FFT calculation
Xfft = abs(fft(x))/Nfft;
Yfft = [Xfft(1), 2*Xfft(2:Nfft/2)]; % Calculate single sided spectrum
f = (0:Nfft/2-1)/Nfft*fs;

% Plot spectrum
subplot(313);
stem(f,Yfft,'o-');
title('Frequency Domain Filtering');
grid;
xlabel('frequency / Hz');
legend('Spectrum of input signal');

