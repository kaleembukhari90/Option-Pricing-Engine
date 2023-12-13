# Option Pricing Engine
Disclaimer: This repository is not intended to be a financial advisory or actionable tool. It is purely a programming project for Financial Engineering.

This repository contains C++ code for an Option Pricing Engine. The Engine is designed to price Plain-Vanilla European Options using the Black-Scholes Formula and Perpetual American Options using an Exact Formula to price those options.

## European Options
The code contains implementation for the Exact Formula for Black-Scholes Model along with the fundamental Option Greeks namely Delta & Gamma. Moreover, Put-Call Parity has also been setup.

Call Option Formula:

$$C = Se^{{(b-r)}T}N(d_1) - Ke^{-rT}N(d_2)$$

Put Option Formula:

$$P = Ke^{-rT}N(-d_2) - Se^{{(b-r)}T}N(-d_1)$$

Where;

$N(x)$ = Cummulative Distribution Function (CDF) of a Standard Normal Random Variable

$$N(x) = \frac{1}{\sqrt{2\pi}} \int_{-\infty}^{x} e^{-y^2/2} \, dy$$
$$d_1 = \frac{\ln(S/K) + (b+\frac{\sigma^2}{2})T}{\sigma \sqrt{T}}$$
$$d_2 = \frac{\ln(S/K) + (b-\frac{\sigma^2}{2})T}{\sigma \sqrt{T}}$$

### Option Greeks
$$\Delta C = \frac{\partial C}{\partial S} = e^{(b-r)T} N(d_1)$$
$$\Gamma C = \frac{\partial^2 C}{\partial S^2} = \frac{\partial \Delta C}{\partial S} = \frac{n(d_1)e^{(b-r)T}}{S_0 \sigma \sqrt{T}}$$

Note: $n(x)$ is the PDF of the a Standard Normal Random Variable

## Perpetual American Options
The code contains implementation of the Exact Formula for pricing Perpetual American Options.

Call Option Formula:
$$C = \frac{K}{y_{1} - 1}\left( \frac {(y_{1} - 1)}{y_{1}} \frac{S}{K}\right) ^{y_{1}}$$


$$y_{1} = \frac{1}{2} - \frac{b}{\sigma^2} + \sqrt{\left(\frac{b}{\sigma^2}-\frac{1}{2}\right)^2 + \frac{2r}{\sigma^2}}$$

Put Option Formula:
$$P = \frac{K}{1 - y_{2}}\left( \frac {(y_{2} - 1)}{y_{2}} \frac{S}{K}\right) ^{y_{2}}$$

$$y_{2} = \frac{1}{2} - \frac{b}{\sigma^2} - \sqrt{\left(\frac{b}{\sigma^2}-\frac{1}{2}\right)^2 + \frac{2r}{\sigma^2}}$$


### General Notations for European and Perpetual American Options

S = Asset Price

K = Strike

T = Time to Expiry

r = Risk-Free Rate

$\sigma$ = Volatility (Constant)

b = Cost of Carry
- b = r (Black Scholes Non-Dividend Equity Options)
- b = r -q (Black Scholes Dividend Paying Equity Options)
- b = 0 (Black-Scholes Futures Option)