G3 = tf([10], [1, 1, 1])
w = 1;
T = 2*pi/w;

t = 0:T/100:30;
u = sin(w*t);
y = lsim(G3, u, t);
plot(t, u, t, y), grid on;


z = evalfr(G3, 1j*w);
m = abs(z) %pe grafic am vazut 10 (iesire > intrare)
mdb = 20*log10(m) %aproximativ 20
faza = 180*angle(z)/pi %defazajul in grade (negativ, -90); iesirea e in intarziere de faza

delta_t = (15.71 - 17.28) %defazajul in timp
phi = delta_t * w %defazajul in radiani
phideg = 180*phi/pi %defazajul in grade 


%%
figure
w = logspace(-2, 2, 2000);
bode(G3, w), grid %se observa defazajul in grade aprox -90deg si magnitudinea 20db





                    