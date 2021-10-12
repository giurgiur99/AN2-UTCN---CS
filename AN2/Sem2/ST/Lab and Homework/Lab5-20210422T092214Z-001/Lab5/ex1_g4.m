G4 = tf([1, 1, 1], [1, 1, 10])
w = 1;
T = 2*pi/w;

t = 0:T/100:30;
u = sin(w*t);
y = lsim(G4, u, t);
plot(t, u, t, y), grid on;


z = evalfr(G4, 1j*w);
m = abs(z) %pe grafic am vazut 0.1 (iesire < intrare)
mdb = 20*log10(m) %aproximativ -19
faza = 180*angle(z)/pi %defazajul in grade (pozitiv, 83); iesirea e in avans de faza

delta_t = (18.85 - 17.34) %defazajul in timp
phi = delta_t * w %defazajul in radiani
phideg = 180*phi/pi %defazajul in grade 


%%
figure
w = logspace(-2, 2, 2000);
bode(G4, w), grid %se observa defazajul in grade aprox 83deg si magnitudinea -19db





                    