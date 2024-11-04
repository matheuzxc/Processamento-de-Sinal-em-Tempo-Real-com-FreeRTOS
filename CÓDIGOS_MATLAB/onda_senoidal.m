function [onda_1,onda,T] = onda_senoidal(Fs, duracao, frequencia, amplitude, noise_amplitude)
    T = 1/Fs;
    t = 0:T:duracao-T;
    onda = amplitude * sin(2*pi*frequencia*t);
    onda_1 = onda;
    if nargin == 5
        % Adição de ruído ao sinal
        onda = onda + noise_amplitude * randn(size(t));
    end
end