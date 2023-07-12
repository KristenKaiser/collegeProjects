import pandas as pd
import numpy as np
from sklearn.linear_model import SGDRegressor
from sklearn.model_selection import train_test_split
from math import sqrt
from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler
from sklearn.metrics import mean_squared_error
from sklearn.metrics import mean_absolute_error
from sklearn import linear_model

from sklearn.pipeline import make_pipeline
from sklearn.preprocessing import StandardScaler
NUM_INPUTS = 8
INPUT_CATS= ['pages', 'avg_reviews', 'n_reviews', 'star5', 'star4', 'star3', 'star2', 'star1']


def get_mae(w, bias, x, y):
    mae = 0
    for i in range(len(x)):
        predicted = 0
        for j in range(NUM_INPUTS):
            predicted += w[j] * x[i][j]
        predicted += bias
        mae = abs(y[i] - predicted)
    return mae/len(x)


def get_mse(w, bias, x, y):
    mse = 0
    for i in range(len(x)):
        predicted = 0
        for j in range(NUM_INPUTS):
            predicted += w[j] * x[i][j]
        predicted += bias
        mse = (y[i] - predicted) * (y[i] - predicted)
    return mse / len(x)


def ols_get_weight(x_list, y_list,):
    x_mean = get_mean(x_list)
    y_mean = get_mean(y_list)
    numerator = 0
    denominator = 0
    for i in range(len(x_list)):
        numerator += (x_list[i]-x_mean)*(y_list[i]-y_mean)
        denominator += (x_list[i]-x_mean)*(x_list[i]-x_mean)
    weight = numerator/denominator
    bias = y_mean - (x_mean * weight)
    return bias, weight


def get_mean(val_list):
    total = 0
    for c in val_list:
        total += c
    return total/len(val_list)


# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    # import data  to data frame
    df = pd.read_csv('book_data.csv')
    x = df[['pages', 'avg_reviews', 'n_reviews', 'star5', 'star4', 'star3', 'star2', 'star1']].to_numpy(dtype=float)
    y = df['price'].to_numpy()

    ols_weights = []
# randomize and split data
    x_train, x_test, y_train, y_test = train_test_split(x, y, test_size=0.2)

    bias = 0.0
# get weights
    for i in range(NUM_INPUTS):
        t_bias, t_weight = ols_get_weight(x_train[:, i], y_train)
        ols_weights.append(t_weight)
        bias += t_bias

# get bias  b=ybar - m*xbar
    bias = get_mean(y_train) - bias
    print("OLS")
    print(" \nparameter vector: ")
    for i in range(NUM_INPUTS):
        print(' (', INPUT_CATS[i], "* %.2f) +" % ols_weights[i], end='')
    print("(%.2f)" % bias)

    print("\ntest set data ")
    print("MSE:", get_mse(ols_weights, bias, x_test, y_test))
    print("MAE:", get_mae(ols_weights, bias, x_test, y_test))
    print("R^2",sqrt(get_mse(ols_weights, bias, x_test, y_test)))

    print("\ntraining set data ")
    print("MSE:", get_mse(ols_weights, bias, x_train, y_train))
    print("MAE:", get_mae(ols_weights, bias, x_train, y_train))
    print("R^2",sqrt(get_mse(ols_weights, bias, x_train, y_train)))


    print("______________________________________________")
    print("\nLinear regression with gradient descent:")
    reg = make_pipeline(StandardScaler(), SGDRegressor(max_iter=1000, tol=1e-3))
    reg.fit(x_train, y_train)
    lin_model = linear_model.Ridge(alpha=.5)
    lin_model.fit(x_train, y_train)

    print("\nparameter vector:")
    for i in range(NUM_INPUTS):
        print(' (', INPUT_CATS[i], "* %.2f) +" % lin_model.coef_[i], end='')
    print("(%.2f)" % lin_model.intercept_)

    print("\ntest set data:")
    mse = mean_squared_error(y_test, reg.predict(x_test))
    print("MSE: ", mse)
    mae = mean_absolute_error(y_test, reg.predict(x_test))
    print("MAE: ", mae)
    score = reg.score(x_test,y_test)
    print("R^2:", score)

    print("\ntraining set data ")
    mse = mean_squared_error(y_train, reg.predict(x_train))
    print("MSE: ", mse)
    mae = mean_absolute_error(y_train, reg.predict(x_train))
    print("MAE: ", mae)
    score = reg.score(x_train,y_train)
    print("R^2:", score)











