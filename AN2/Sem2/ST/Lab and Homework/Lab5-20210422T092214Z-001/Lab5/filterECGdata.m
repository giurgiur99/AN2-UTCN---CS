[num, den] = butter(4, [0.5*2*pi, 50*2*pi], 'bandpass', 's');
butter_filter = tf(num, den)

figure, bode(butter_filter), grid on;

G2 = tf([100*pi, 1], conv([1, pi], [1, 100*pi]))

G4 = G2*G2;
G8 = G4*G4;

figure, bode(G2, G4, G8);

figure, lsim(butter_filter, G8, necg, time), grid on;