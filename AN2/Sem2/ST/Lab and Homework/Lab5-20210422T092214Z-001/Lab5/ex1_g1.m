G1 = tf([0.1, 1], [1, 1])
w = 1;
T = 2*pi/w;

t = 0:T/100:30;
u = sin(w*t);
y = lsim(G1, u, t);
plot(t, u, t, y), grid on;


z = evalfr(G1, 1j*w);
m = abs(z) %pe grafic am vazut 0.7104, 0.7105
mdb = 20*log10(m) %aproximativ -3
faza = 180*angle(z)/pi %defazajul in grade (negativ, -39), iesirea e in intarziere de faza

delta_t = (15.71 - 16.4) %defazajul in timp
phi = delta_t * w %defazajul in radiani
phideg = 180*phi/pi %defazajul in grade


%%
figure
w = logspace(-2, 2, 2000);
bode(G1, w), grid %se observa defazajul in grade aprox -39deg si magnitudinea -3db





                    