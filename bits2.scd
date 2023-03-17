// these are variations on http://sccode.org/1-5ei#c1021
// my variations are based on bytebeat stuff I did for the midiboy, arduino code
// here https://github.com/poetaster/bytebeats/blob/master/bytebeats.ino
// that thing draws pictures, too.

//  t / 13 >> (1 + ((t >> 12) & 3)) | i / 2 >> 2 & (t / 6) >> 7 | t & 31 * t * (i >> 8)
// (t / 3 >> (t % 40 + 5) | t / (24 + t & 3) >> (t % (15 - ((t >> 15) % 8) * 6) + 5)) / 8

// one
(
	Ndef(\bits1, {
		var t = PulseCount.ar(Impulse.ar(8e3));
		var u = PulseCount.ar(Impulse.ar(7009));
		var sig = HPF.ar(
			(
			    ((t >> 12) | (t >> 8) & (63 & t) >> 4)
				- 3 % 256
			) / 127-1 * 3
			, 20
		) * 0.1;
		var sig2 = LPF.ar(HPF.ar(gcd(t*u, u+t), WhiteNoise.ar()*2000 + 1000), 20);
		sig2 = sig2*sig;
		sig = 0.3*Splay.ar( Limiter.ar( Greyhole.ar(sig + sig2, sig, 0.5, sig), 0.5).flatten);
	}).play;
)

// two
(
	Ndef(\bits2, {
		var t = PulseCount.ar(Impulse.ar(8e3));
		var u = PulseCount.ar(Impulse.ar(7009));
		var sig = HPF.ar(
			(
			(t / 3 >> (t % 40 + 5)) | ((t / (24 + t & 3) >> (t % (15 - ((t >> 15) % 8) * 6) + 5)) / 8)
				- 3 % 256
			) / 127-1 * 3
			, 20
		) * 0.1;
		var sig2 = LPF.ar( HPF.ar(gcd(t*u, u+t), WhiteNoise.ar()*2000 + 1000), 20);
		sig2 = sig2*sig;
		sig = 0.3*Splay.ar( Limiter.ar( Greyhole.ar(sig + sig2, sig, 0.5, sig), 0.5).flatten);
	}).play.scope;
)

(
	Ndef(\bits3, {
		var t = PulseCount.ar(Impulse.ar(8e3));
		var u = PulseCount.ar(Impulse.ar(7009));
		var sig = HPF.ar(
			(
			    ( t / 13 >> (1 + ((t >> 12) & 3))) |
			    ( t / 2 >> 2 & (t / 6) >> 7 ) |
			    (t & 31 * t * (t >> 8))
				- 3 % 256
			) / 127-1 * 3
			, 20
		) * 0.1;
		var sig2 = LPF.ar( HPF.ar(gcd(t*u, u+t), WhiteNoise.ar()*2200 + 1000), 20);
		sig2 = sig2*sig;
		sig = 0.3* Splay.ar( Limiter.ar( Greyhole.ar(sig + sig2, sig, 0.5, sig), 0.5).flatten);
	}).play.scope;
)

// four is slow, minimal. very.
(
	Ndef(\bits4, {
		var t = PulseCount.ar(Impulse.ar(8e3));
		var u = PulseCount.ar(Impulse.ar(7009));
		var sig = HPF.ar(
			(
			    (t ** t >> 8) | (t << 3 & 56 ** t)
				- 3 % 32
			) / -3 % 16
			, 20
		) * 0.1;
		var sig2 = LPF.ar( HPF.ar(gcd(t*u, u+t), WhiteNoise.ar()*2200 + 1000), 20);
		sig2 = sig2*sig;
		sig = 0.3* Splay.ar( Limiter.ar( Greyhole.ar(sig + sig2, sig, 0.5, sig), 0.5).flatten);
	}).play.scope;
)

(
	Ndef(\bits5, {
		var t = PulseCount.ar(Impulse.ar(7099));
		var u = PulseCount.ar(Impulse.ar(7009));
		var sig = HPF.ar(
			(
			    t * ((t >> 12 | t >> 8) & 63 & t >> 4)
			    - 3 % 32
			) / -3 % 16
			, 25
		) * 0.1;
		var sig2 = LPF.ar( HPF.ar(gcd(t*u, u+t), WhiteNoise.ar()*2000 + 1001), 20);
		sig2 = sig2*sig;
		sig = 0.3* Splay.ar( Limiter.ar( Greyhole.ar(sig + sig2, sig, 0.5, sig), 0.5).flatten);
	}).play.scope;
)

// really sci fi ... astroid belt mining operation.
(
	Ndef(\bits5, {
		var t = PulseCount.ar(Impulse.ar(8e3));
		var u = PulseCount.ar(Impulse.ar(7009));
		var sig = HPF.ar(
			(
			  ( ( ( ( (t>>12) ** (t>>12) -2 ) %11 *t ) /4 | t>>13 ) & 127)
			)
			, 20
		) * 0.1;
		var sig2 = LPF.ar( HPF.ar(gcd(t*u, u+t), WhiteNoise.ar()*1900 + 800), 10);
		sig2 = sig2*sig;
		sig = 0.3* Splay.ar( Limiter.ar( Greyhole.ar(sig + sig2, sig, 0.5, sig), 0.5).flatten);
	}).play.scope;
)

