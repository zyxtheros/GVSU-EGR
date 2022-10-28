% Contributer - Pierce Foster
% Date Completed: 10/26/2022
% Class: EGR 346-20
% Program Information: This program provides all the needed data values to
% create the SSR of the system. All units are either converted or given in
% standard SI form.

step=0.01;
t_set=0:step:20;
t=t_set.';

%Easily change the speed, amplitude, and wavelength with multipliers
SETSPEED=75*.1
SETAMP=0.05*10
SETWAVELENGTH=8*5

K_f=36000;                       %N/m
K_r=24000;                       %N/m
B_f=4000;                        %N-s/m
B_r=3000;                        %N-s/m
L_f=41.72/39.37;                 %in to m
L_r=62.58/39.37;                 %in to m
m=1762;                          %kg
J=3072;                          %kg m^2

speed=SETSPEED/3.6;              %km/h to m/s
Amp=SETAMP;                      %m
lambda=SETWAVELENGTH;            %m
freq=speed/lambda;               %1/s
t_r=(L_f+L_r)/speed;             %s - this is the time it takes for the back wheel to reach the first bump

w=2*pi*freq;
phi=2*pi*t_r*freq;
Z_in_f=Amp*sin(w*t);
Z_in_r=Amp*sin(w*t-phi);
Z_in_f_dot=Amp*w*cos(w*t);
Z_in_r_dot=Amp*w*cos(w*t-phi);

A=[0,1,0,0;
   -(L_f^2*K_f+L_r^2*K_r)/J,-(L_f^2*B_f+L_r^2*B_r)/J,-(-L_f*K_f+L_r*K_r)/J,-(-L_f*B_f+L_r*B_r)/J;
   0,0,0,1;
   -(-L_f*K_f+L_r*K_r)/m,-(-L_f*B_f+L_r*B_r)/m,-(K_f+K_r)/m,-(B_f+B_r)/m];
B=[0,0,0,0;
   -K_f*L_f/J,-B_f*L_f/J,K_r*L_r/J,B_r*L_r/J;
   0,0,0,0;
   K_f/m,B_f/m,K_r/m,B_r/m];
C=[0 0 1 0;
   1 0 0 0];
D=[0,0,0,0;0,0,0,0];

%from zero to t_r, the rear is still driving on flat ground
%u3 and u4 are adjusted in order to display this

u1=horzcat(t,Z_in_f);
u2=horzcat(t,Z_in_f_dot);
u3=horzcat(t,Z_in_r);
u4=horzcat(t,Z_in_r_dot);

u3_4_adjust_time = round(t_r/step);
for i=1:1:u3_4_adjust_time
    u3(i,2)=0;
    u4(i,2)=0;
end