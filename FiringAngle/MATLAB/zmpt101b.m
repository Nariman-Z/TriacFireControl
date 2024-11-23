clc
close all
clear all

% Sample data
analogReadings = [350, 420, 512, 680, 760]; % Raw sensor readings
actualVoltages = [110, 150, 220, 300, 350]; % Actual AC voltages

% Plot the raw data
figure;
plot(analogReadings, actualVoltages, 'o');
xlabel('Analog Reading (from ZMPT101B)');
ylabel('Actual AC Voltage (V)');
title('Calibration Data: ZMPT101B Sensor');
grid on;
hold on;

% Linear regression using polyfit
p = polyfit(analogReadings, actualVoltages, 1); % Linear fit (y = p(1)*x + p(2))
fitLine = polyval(p, analogReadings);
plot(analogReadings, fitLine, '-r');
legend('Data Points', 'Calibration Line');

% Display equation
fprintf('Calibration Equation: Voltage = %.2f * Reading + %.2f\n', p(1), p(2));