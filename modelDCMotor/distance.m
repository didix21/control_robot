function r = distance(params)
% (J) moment of inertia of the rotor
% (b) motor viscous friction constant
% (K) electromotive force constant and motor torque constant
% (R) electric resistance
% (L) electric inductance
J=params(1); b=params(2); K=params(3);
R=params(4); L=params(5);
A=[-b/J K/J; -K/L R/L]
B=[0; 1/L];
C=[1,0];
D=0;
eigenValues = eig(A);
sys=ss(A,B,C,D);
%Now we discretize the systsem with the same
%rate the data was provided
h=0.1;
if ((real(eigenValues(1))<=0) && (real(eigenValues(2))<=0) &&(R>=0) && (b>=0) && (J>=0))
sysd=c2d(sys,h);
%And now we simulate the response
global u %system input, recorded with arduino
global t %timming of the input
global y %Real output recorded with arduino
[y_model,t]=lsim(sysd,u,t);
    r=norm(y-y_model);
else
    r = inf;
end
end

