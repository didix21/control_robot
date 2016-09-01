load dades.mat
close all
y_rpm = vector(101:300);
y_pwmModel_cut = vector(101:300);


pwm = zeros(200,1);
for i = 1:156
    pwm(i) = 99 + i;
end
 pwm(157:end)=255;
%%
 p = polyfit(pwm,y_rpm,2);
 pwm_model = zeros(300,1);
 pwm_model(1) = 0;
 pwm_model(1:255,1) = 1:255;
 pwm_model(256:end,1) = 255;
y_pwmModel = zeros(length(pwm_model),1);
for i = 1:length(pwm_model)
    y_pwmModel(i) = p(1)*pwm_model(i)^2 +p(2)*pwm_model(i)+p(3);
end


plot(pwm,y_rpm)
hold on
for i= 1:200
y_pwmModel_cut(i)=y_pwmModel(i+99);
end
plot(pwm,y_pwmModel_cut,'r')
title ('Gràfica de linealització de la velocitat');
xlabel ('Temps (Segons)');
ylabel ('Velocitat');
legend('Motor','Linealitzat');