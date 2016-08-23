global y u t;
load motorDreta.mat
y = motorD(201:600,1);
a = 1;

%%

u=zeros(length(y),1);
a = 1;
for j=1:(length(y)/100)
    switch a
        case 1
            for i=1+(j-1)*100:100+(j-1)*100
                u(i)=245;
            end
            a = 2;
        case 2
            for i=1+(j-1)*100:100+(j-1)*100
                u(i)=165;
            end
            a = 1;
    end
end
t = zeros(length(y),1);

for i=2:(length(y))
    t(i) = t(i-1) + 0.1;
end
%%
J = 1;
K = 1;
b = 1;
L = 1;
R=1;
params = [J b K R L];
newParams = fminsearch(@distance,params)
%%
J = newParams(1);
b = newParams(2);
K = newParams(3);
R = newParams(4);
L = newParams(5);

A=[-b/J K/J; -K/L R/L]
B=[0; 1/L];
C=[1,0];
D=0;

sys_model=ss(A,B,C,D);
[y_model,t] = lsim(sys_model,u,t);
plot(y_model)