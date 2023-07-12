import pandas as pd
import numpy as np
from sklearn.model_selection import train_test_split
from sklearn.linear_model import SGDClassifier
from sklearn.linear_model import LogisticRegression
from sklearn.preprocessing import StandardScaler
from sklearn.pipeline import make_pipeline
from sklearn.naive_bayes import GaussianNB
from sklearn.metrics import f1_score
from sklearn.metrics import accuracy_score
from sklearn.metrics import log_loss


def compare_lists(actual, predicted):
    true_pos = 0
    true_neg = 0
    false_pos = 0
    false_neg = 0
    for i in range(len(actual)):
        if predicted[i] == 1:
            if actual[i] == 1:
                true_pos = true_pos + 1
            else:
                false_pos = false_pos + 1
        else:
            if actual[i] != 1:
                true_neg = true_neg + 1
            else:
                false_neg = false_neg + 1
    return true_pos, true_neg, false_pos, false_neg


# get file
df = pd.read_csv('data.csv')
# extract input and output
x = df[['math score', 'reading score', 'writing score']].to_numpy()
y = df['isParentCollegeGrad'].to_numpy()
# randomizes then split into training and testing sets
x_train, x_test, y_train, y_test = train_test_split( x, y, test_size= 0.2)

# logistic regression
clf = LogisticRegression().fit(x_train, y_train)
test_predict = clf.predict(x_test)
train_predict = clf.predict(x_train)

test_log_tp, test_log_tn, test_log_fp, test_log_fn = compare_lists(y_test, test_predict)
train_log_tp, train_log_tn, train_log_fp, train_log_fn = compare_lists(y_train, train_predict)

print('logistic regression')
print("")

print('accuracy (test set): ', accuracy_score(y_test, test_predict))
print('sensitivity(test set): ', test_log_tp/(test_log_tp + test_log_fn))
print('specificity(test set): ', test_log_tn/(test_log_tn + test_log_fp))
print("f1 (test set): ", f1_score(y_test,test_predict))
print('log loss (test set): ', log_loss(y_test, test_predict))
print("score (test set): ", clf.score(x_test, y_test))
print("")

print('accuracy (train set): ', accuracy_score(y_train, train_predict))
print('sensitivity (train set): ', train_log_tp/(train_log_tp + train_log_fn))
print('specificity (train set): ', train_log_tn/(train_log_tn + train_log_fp))
print("f1 (train set): ", f1_score(y_train,train_predict))
print('log loss (train set): ', log_loss(y_train, train_predict))
print("score (train set): ", clf.score(x_train, y_train))
print("")

print('w = ', clf.intercept_, '+ (', clf.coef_[[0],[0]], '* math score +', clf.coef_[[0],[1]], '* reading score +',
      clf.coef_[[0],[2]], '* writing score)')

gnb = GaussianNB().fit(x_train, y_train)
gnb_test_predict = gnb.predict(x_test)
gnb_train_predict = gnb.predict(x_train)
test_bayes_tp, test_bayes_tn, test_bayes_fp, test_bayes_fn = compare_lists(y_test, gnb_test_predict)
train_bayes_tp, train_bayes_tn, train_bayes_fp, train_bayes_fn = compare_lists(y_train, gnb_train_predict)

print("")
print("")
print('Naive Bayes')
print("")

print('accuracy (test set): ', accuracy_score(y_test, gnb_test_predict))
print('sensitivity(test set): ', test_bayes_tp/(test_bayes_tp + test_bayes_fn))
print('specificity(test set): ', test_bayes_tn/(test_bayes_tn + test_bayes_fp))
print("f1 (test set): ", f1_score(y_test,gnb_test_predict))
print('log loss (test set): ', log_loss(y_test, gnb_test_predict))
print("score (test set): ", gnb.score(x_test, y_test))
print("")

print('accuracy (train set): ', accuracy_score(y_train, gnb_train_predict))
print('sensitivity (train set): ', train_bayes_tp/(train_bayes_tp + train_bayes_fn))
print('specificity (train set): ', train_bayes_tn/(train_bayes_tn + train_bayes_fp))
print("f1 (train set): ", f1_score(y_train,gnb_train_predict))
print('log loss (train set): ', log_loss(y_train, gnb_train_predict))
print("score (train set): ", gnb.score(x_train, y_train))
print("")

# print('w = ', clf.intercept_, '(', clf.coef_[[0],[0]], '* math score +', clf.coef_[[0],[1]], '* reading score +',
      # clf.coef_[[0],[2]], '* writing score)')
