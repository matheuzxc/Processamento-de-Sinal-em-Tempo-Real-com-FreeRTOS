Fs = 100;           % Taxa de amostragem
duracao = 10;        % Duração da onda em segundos
frequencia = 5;     % Frequência da onda senoidal em Hz
amplitude = 1;      % Amplitude da onda senoidal
noise_amplitude = 1.2;  % Amplitude do ruído

% Geração da onda senoidal
[onda_1, onda] = onda_senoidal(Fs, duracao, frequencia, amplitude, noise_amplitude);
[fx, s_f] = fourier(onda, Fs);

% Visualização da onda senoidal
figure(1);

subplot(2,1,1), plot(0:1/Fs:duracao-1/Fs, onda);
title('Onda Senoidal Gerada');
xlabel('Tempo (s)');
ylabel('Amplitude');

subplot(2,1,2), plot(fx, s_f);
grid on;
title('Transformada de Fourier da Onda Senoidal');
xlabel('Frequência (Hz)');
ylabel('Amplitude');

% Filtro Chebyshev Tipo I
figure(2);
n = 3;
wp = 6;
wn = 30/(Fs/2);
[num, den] = cheby1(n, wp, wn, 'low');
sys = tf(num, den, 1/Fs);
sfiltrada = filter(num, den, onda);

% Visualização do sinal filtrado
subplot(2,1,1), plot(0:1/Fs:duracao-1/Fs, sfiltrada);
title('Sinal Filtrado');
grid on;
xlabel('Tempo (s)');
ylabel('Amplitude');

[fsfiltrada, s_filtrada] = fourier(sfiltrada, Fs);
subplot(2,1,2), plot(fsfiltrada, s_filtrada);
title('Transformada de Fourier do Sinal Filtrado');
grid on;
xlabel('Frequência (Hz)');
ylabel('Amplitude');