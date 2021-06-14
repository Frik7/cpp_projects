#define _USE_MATH_DEFINES

#include <iostream>
#include <cmath>
#include <string>
#include <cstdlib>

using namespace std;

double single_path(double spot, double r, double vol, double maturity)
    {

        double f1 = (r - 0.5*vol*vol)*maturity;
        double rand_uniform1 = (double) rand()/RAND_MAX;
        double rand_uniform2 = (double) rand()/RAND_MAX;
        double rand_normal = pow(-2*log(rand_uniform1),0.5)*cos(2*M_PI*rand_uniform2); // Box-Muller Transform
        double f2 = vol*pow(maturity, 0.5)*rand_normal;

        return spot*exp(f1 + f2);
    }

int main()
{
    string type;
    double spot;
    double strike;
    double r;
    double vol;
    double maturity;
    int paths;

    srand((unsigned) time(nullptr));
    double payoff_sum = 0;
    
    cout << "Please enter the option parameters." << endl;
    cout << "Type of option. Call or Put: ";
    cin >> type;
    cout << "Spot price of the underlying: ";
    cin >> spot;
    cout << "Strike price of the Option Contract: ";
    cin >> strike;
    cout << "Riks free rate in decimal notation: ";
    cin >> r;
    cout << "Annualized volatility of the underlying: ";
    cin >> vol;
    cout << "Time, in years, to maturity: ";
    cin >> maturity;
    cout << "Number of simulated paths: ";
    cin >> paths;

    if (type == "Call")
        {
            for ( int i = 0; i < paths; i++)
            {
                double St = single_path(spot, r, vol, maturity);
                double payoff = St - strike;
                if (payoff > 0 && !(isinf(payoff)))
                {
                    payoff_sum = payoff_sum + payoff;
                }
            }
            
            double option_price = exp(-r*maturity)*(payoff_sum/paths);
            cout << "The price of the option is: " << option_price << endl;
        } else if (type == "Put")
        {
            for ( int i = 0; i < paths; i++)
            {
                double St = single_path(spot, r, vol, maturity);
                double payoff = strike - St;
                if (payoff > 0)
                {
                    payoff_sum = payoff_sum + payoff;
                }
            }
            
            double option_price = exp(-r*maturity)*(payoff_sum/paths);
            cout << "The price of the option is: " << option_price << endl;   
        } else
        {
            cout << "The incorrect option type was entered. Please start over." << endl;
        }

    system("pause");
    
    return 0;
}

