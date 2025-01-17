#pragma once
#include <vector>
#include <string>
namespace dmlc {
namespace difacto {

struct Progress {
  Progress() : data(9) { }

  static std::string HeadStr() {
    return "  ttl #ex   inc #ex |  |w|_0  logloss_w |   |V|_0    logloss    AUC    RMSE";
  }

  std::string PrintStr() {

    if (data.size() < 8) data.resize(8,0);
    ttl_ex += new_ex();
    nnz_w += new_w();
    nnz_V += new_V();

    if (new_ex() == 0) return "";

    char buf[256];
    snprintf(buf, 256, "%9.4g  %7.2g | %9.4g  %6.4lf | %9.4g  %7.5lf  %7.5lf  %7.5lf ",
             ttl_ex, new_ex(), nnz_w, objv_w() / new_ex(), nnz_V,
             objv() / new_ex(),  auc() / count(),  rmse());
    return std::string(buf);
  }

  double& objv() { return data[0]; }
  double& auc() { return data[1]; }
  double& objv_w() { return data[2]; }
  double& copc() { return data[3]; }

  double& count() { return data[4]; }
  double& new_ex() { return data[5]; }
  double& new_w() { return data[6]; }
  double& new_V() { return data[7]; }
  double& rmse() { return data[8]; }

  double objv() const { return data[0]; }
  double new_ex() const { return data[5]; }

  std::vector<double> data;
  double ttl_ex = 0, nnz_w = 0, nnz_V;
};

}  // namespace difacto
}  // namespace dmlc
