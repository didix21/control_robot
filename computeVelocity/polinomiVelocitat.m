load dades.mat

y_rpm = vector(101:300);


pwm = zeros(200,1);
for i = 1:156
    pwm(i) = 99 + i;
end
 pwm(157:end)=255;
%%
 p = polyfit(pwm,y_rpm,2);
 pwm_model = 1:255;
y_pwmModel = zeros(length(pwm_model),1);
for i = 1:length(pwm_model)
    y_pwmModel(i) = p(1)*pwm_model(i)^2 +p(2)*pwm_model(i)+p(3);
end

