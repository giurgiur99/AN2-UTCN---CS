G2 = tf([10, 10], [1, 10])
w = 1;
T = 2*pi/w;

t = 0:T/100:30;
u = sin(w*t);
y = lsim(G2, u, t);
plot(t, u, t, y), grid on;


z = evalfr(G2, 1j*w);
m = abs(z) %pe grafic am vazut 1.4 (iesire > intrare)
mdb = 20*log10(m) %aproximativ 3
faza = 180*angle(z)/pi %defazajul in grade (pozitiv, 39); iesirea e in avans de faza

delta_t = (15.71 - 15.02) %defazajul in timp
phi = delta_t * w %defazajul in radiani
phideg = 180*phi/pi %defazajul in grade 


%%
figure
w = logspace(-2, 2, 2000);
bode(G2, w), grid %se observa defazajul in grade aprox 39deg si magnitudinea 3db





                    