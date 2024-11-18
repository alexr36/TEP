#include <iostream>

#include "CError.h"
#include "CResult.h"

CResult<double, CError> eDivide(double dDividend, double dDivisor) {
    if (dDivisor == 0) return CResult<double, CError>::fail(new CError("Cannot divide by zero"));

    return CResult<double, CError>::ok(dDividend / dDivisor);
}

int main() {
    CResult<double, CError> result = eDivide(10.0, 0.0);

    if (result.isSuccess()) {
        std::cout << "Result: " << *result.getValue() << std::endl;
    }
    else {
        std::vector<CError*>& errors = result.getErrors();

        for (size_t i = 0; i < errors.size(); i++) {
            std::cout << "Error: " << errors[i]->getMessage() << std::endl;
        }
    }

    return 0;
}
