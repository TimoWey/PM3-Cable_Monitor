%% Calculate the E- and B-fields of a mains cable
% Voltage set to 230V
% Current normalised to 1A
% (c) hhrt@zhaw.ch 06.02.2020
clc; clear; close all;
format compact; format short eng;

%% Geometry             % All dimensions in m or m2
A_wire = 1.5e-6;        % Conductor cross-section in m2
d_wires = 2.6e-3;       % Outer diameter of isolated conductor = distance of wire centers
d_pad = 25e-3;          % Length of pad which picks up the electric field of the wire

%% Pre-calculation
r_wire = sqrt(A_wire/pi);        % Radius of the wire
N = 115; inc = r_wire/2;         % Grid dimension and grid spacing in mm
[X,Y] = meshgrid(inc*(-N:1:N), inc*(-N:1:N));

scrsz   = get(0,'ScreenSize');
figure('name', 'Capacity to earth and H-field of one wire and of two wires', 'Position',[10,10,scrsz(3)-20,scrsz(4)-100])

%% Calculate capacity of pad to wire
%  Approach: Calculate capacity with formula for parallel wires
%  As with capacitors in series the smaller value is dominant, the
%  length of the pad and the radius of the wire are taken for calculation.
%  The capacitance value is thus a bit underestimated.

distance = sqrt(X.^2+Y.^2);
C = 8.85e-12*pi*d_pad ./ log(distance/r_wire);
Cmax = 8.85e-12*pi*d_pad / log(2);  % Limit when wire and pad touch
C(1+N-2:1+N+2,1+N-2:1+N+2) = Cmax;
subplot(331);
v = Cmax*logspace(-3,0);
contour(X,Y,C,v); axis equal;
title('capacitance wire-to-pad');
xlabel('distance / m');
subplot(332);
plot(X(1+N,:), C(1+N,:));
title('capacitance wire-to-pad');
grid; ylabel('capacitance / F'); xlabel('distance / m');
axis([-N*inc, N*inc, Cmax/100, Cmax]);
subplot(333);
semilogy(X(1+N,:), abs(C(1+N,:)));
title('capacitance wire-to-pad');
grid; ylabel('capacitance / F'); xlabel('distance / m');
axis([-N*inc, N*inc, Cmax/100, Cmax]);

%% Calculate B-field of one wire
u = 1.257e-6;
R = sqrt(X.*X + Y.*Y);
B = u./(2*pi*R);
Bmax = u./(2*pi*d_wires/2);    % Limit when wire touched
B = min(B, Bmax);        % B-field would decrease in the the wire
subplot(334);
v = Bmax*logspace(-3,0);
contour(X,Y,B,v); axis equal;
title('B-field of one wire');
xlabel('distance / m');
subplot(335);
plot(X(1+N,:), B(1+N,:));
title('B-field of one wire');
grid; ylabel('B-field / T'); xlabel('distance / m');
axis([-N*inc, N*inc, Bmax/100, Bmax]);
subplot(336);
semilogy(X(1+N,:), abs(B(1+N,:)));
title('B-field of one wire');
grid; ylabel('|B-field| / T'); xlabel('distance / m');
axis([-N*inc, N*inc, Bmax/100, Bmax]);

%% Calculate resulting B-field of two parallel wires in same cable
R1 = sqrt((X+d_wires/2).*(X+d_wires/2) + Y.*Y);
B1 = u./(2*pi*R1);
B1 = min(B1, Bmax);         % B-field would decrease in the the wire
R2 = sqrt((X-d_wires/2).*(X-d_wires/2) + Y.*Y);
B2 = -u./(2*pi*R2);    % Current in oposite direction
B2 = max(B2, -Bmax);        % B-field would be 0 in the center of the wire
B12 = B1 + B2;
subplot(337);
v = Bmax*logspace(-3,0);
contour(X,Y,abs(B12),v); axis equal;
title('B-field of two parallel wires');
xlabel('distance / m');
subplot(338);
plot(X(1+N,:), B12(1+N,:), X(1+N,:), B1(1+N,:), X(1+N,:), B2(1+N,:));
title('B-field of two parallel wires');
grid; ylabel('B-field / T'); xlabel('distance / m');
axis([-N*inc, N*inc, -Bmax, Bmax]);
subplot(339);
semilogy(X(1+N,:), abs(B12(1+N,:)));
title('B-field of two parallel wires');
grid; ylabel('|B-field| / T'); xlabel('distance / m');
axis([-N*inc, N*inc, Bmax/100, Bmax]);
