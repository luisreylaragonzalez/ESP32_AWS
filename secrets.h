#include <pgmspace.h>

#define SECRET
#define THINGNAME "MyESP32"                                       //change this

const char WIFI_SSID[] = "Equinox";                                        //change this
const char WIFI_PASSWORD[] = "Oaxaca2021+";                                    //change this
const char AWS_IOT_ENDPOINT[] = "a1dteiqal84vxo-ats.iot.us-east-1.amazonaws.com";        //change this

// Amazon Root CA 1
static const char AWS_CERT_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

// Device Certificate                                               //change this
static const char AWS_CERT_CRT[] PROGMEM = R"KEY(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUA/mXs7NuSZD1WVhwXuXsPdFL9DQwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTIxMDUxOTIyMTAw
N1oXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANo34xThBk7PvlpmtRAv
PWDA9x3E2VU8nUgl/BabMzLJ0m7vLtyx5NZdc8B9CJl4fgc2+jAKuzMuUK+S9Au2
F+HyD0ntmqBevvdBdqau2ypn+LVCxRHd0qkKo18/fvEQZgenUsN+KkTu7xmfOJeA
a6zMnZpXx21+nN/LSR8OcrbPYmKJRWTXA0mWt7LQlrbQN9i5Juo5E0dHmO5hOyXG
qNHeY61M1/3l/QNHIE1/YvlJA1dy+NMF81AqCaamCACWPim5oYNv3GAWElKb0NO/
CprJujfYLyuhbZXODKrj+3LVg5dOj/P5w6jRtezLwA1n6AIZn5SrHlGcYUp90LQ+
D9ECAwEAAaNgMF4wHwYDVR0jBBgwFoAUjVrOoImFEu/g8PDaKTjkEAiwgPowHQYD
VR0OBBYEFFbO4J60PdcoyJ2HGshtP3DL/a8PMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBZ2+vOymCtI7Ty9g0m1v5F4cDw
oUSAc1CzYClhrdGASV/g4mTnfCV9InDO8ThL055FRY7Z15QBAmlsTo1xWZnxg1SP
bLEHeI6CxesTJqOWagHuyKFajqhMDfAuySoyYH2kJN2IxDTwUsFG3He1qTsi8Eq/
txEtftTricoibnha1rUr3lqs9PvcnglialkneeUjiCJv6P56kqpBIjKkczZNUGZC
d2WtPlOiu+sqFoRDjrvJf7UJwUemdZrnwxK+1S94ZP4VwDls3K23kTI/PAbsPS43
HSYsr1rT8fuOHMTcnMywjM6z/HOA2vx4LA55aZNudAIJGFVf2iey8NGphSu7
-----END CERTIFICATE-----
)KEY";

// Device Private Key                                               //change this
static const char AWS_CERT_PRIVATE[] PROGMEM = R"KEY(
-----BEGIN RSA PRIVATE KEY-----
MIIEpQIBAAKCAQEA2jfjFOEGTs++Wma1EC89YMD3HcTZVTydSCX8FpszMsnSbu8u
3LHk1l1zwH0ImXh+Bzb6MAq7My5Qr5L0C7YX4fIPSe2aoF6+90F2pq7bKmf4tULF
Ed3SqQqjXz9+8RBmB6dSw34qRO7vGZ84l4BrrMydmlfHbX6c38tJHw5yts9iYolF
ZNcDSZa3stCWttA32Lkm6jkTR0eY7mE7Jcao0d5jrUzX/eX9A0cgTX9i+UkDV3L4
0wXzUCoJpqYIAJY+Kbmhg2/cYBYSUpvQ078Kmsm6N9gvK6Ftlc4MquP7ctWDl06P
8/nDqNG17MvADWfoAhmflKseUZxhSn3QtD4P0QIDAQABAoIBAQDDrfnjbyXI5mE7
j34t1S6k5GS0PSDmXkRrviQf4Ww3zuL0t2a+YIdj8skpgvWDKZlZvuL60aSscIvJ
5W0SU2d3JSiwknBl/pAgCIPtVD8T98f+QrGVI+UT0IZPkxCx+pKDqnd89lXRGrEt
uKl2saHcgl+RV8VtWmwyAoi/YKVdZ1JZkzFILICkpvb+LVmz8t0OBO8YNLoN+jEC
XipqpU+icutLzk2S02yDTirpTAWxElo1KXqkgUr5Tgksy/+OQjA3R+bKz1oXxMWU
dos4qtA2KsMtANEAUdDZwpcxkpzGttDbw+1Axf56QSrErKkixg4qSh/kYvf0r8pD
IH5CocBBAoGBAO5eaproiC9LB8L2lWbiS11OrvSSfRkGzTBUvru5zPCiTzkpdTBZ
8m9/7BFcCfi+fft6C1IBjh2nKFd24Qvpag2C5fQGixTiuiNGVDQfNjY+z3mIlTzc
/FuSpdP28QH2ylvfV/mhls1ejdk7PCMhtrUtUS48DmB9cqMC7BEKrMrvAoGBAOpb
6jS3a9qKenvbXgBcPEs8mM+X6MiLqeCQpbfE12IlF+xHynDsOUDiy47yDkRBzCqc
gAv1YVMR7qhhuGKkGA3UysPHg2PcSt6PHo++rx/oTRUozAz/G3tYUBWgdfGjRI2b
BI6idId4Mo4eZYZpJtgnITGCayHzfkqRiqIqpdE/AoGBANABehuFkNlcKwC5trPa
AxQARnHLpviA0+s5+FrOjwTpTiK+h7HSu9kKkxCu9VCnwj4BSQGds8syg+SXK1j+
rXnu4QVp9FIca3u+slntZpw9gUU3p6s918V9GdH26mbhWcKECjwfAv5hZXzL0PWD
RPGjAvVKmO0gaznOoftZCmHnAoGAYWJ6axeBENoUVZ1tbVbmkxkGItVsHNG0cKWK
x1dbbOQfEccvP0dZ7zWPAsJg3Uo+LcLEjrOTkrJT6tJYjVzExhKTg1FHrtpenib4
uyCwouCkD1PZntjvMY0cEjCQci23EeTFuwOUyqpOz7Gf3H+bbZys9WbNX9lPtGrQ
Idz49H8CgYEAntzZI7wMvJUnpEI7WrcimD//TjNQH4PEz0re2MJWxZFnsVPrQmgM
NF/XnuZQVFJCtZmhhMGvMmpobwmtZ4LDelnBQXrz9ric3tIUIrq3u30Suw/PwLOQ
USIbA30AVOvMjPJVshjxuaGhXunRNWI26xV5oNHtmM9VOZLUl1KoIQo=
-----END RSA PRIVATE KEY-----
)KEY";
