#include "TemplateParser.h"

// 这些库并非全部需要，根据需要使用
#include <algorithm>
#include <map>
#include <set>
#include <unordered_map>
using namespace std;


string get_str(const TemplateFunction &f) {
  string s = "Resolved to: " + f.name + "(";
  for (int i = 0; i < f.parameters.size(); ++i) {
    if (i)
      s += ", ";
    s += f.parameters[i].name;
  }
  s += ")";
  if (f.is_template)
    s += " [template]";
  return s;
}

static bool match_non_template(const TemplateFunction &f, const CallSite &cs) {
  if (f.is_template) return false;
  if (f.name != cs.function_name) return false;
  if (f.parameters.size() != cs.arguments.size()) return false;
  for (size_t i = 0; i < f.parameters.size(); ++i) {
    if (f.parameters[i] != cs.arguments[i]) return false;
  }
  return true;
}

static bool match_template(const TemplateFunction &f, const CallSite &cs) {
  if (!f.is_template) return false;
  if (f.name != cs.function_name) return false;
  if (f.parameters.size() != cs.arguments.size()) return false;

  map<string, string> binding; // 模板形参名 -> 实参类型名
  for (size_t i = 0; i < f.parameters.size(); ++i) {
    const Type &fp = f.parameters[i];
    const Type &ap = cs.arguments[i];
    if (fp.is_template_param()) {
      auto it = binding.find(fp.name);
      if (it == binding.end()) {
        binding[fp.name] = ap.name; // 首次绑定
      } else {
        if (it->second != ap.name) return false; // 绑定冲突
      }
    } else {
      if (fp != ap) return false;
    }
  }
  return true;
}
static int count_template_params(const TemplateFunction &f) {
  int cnt = 0;
  for (const auto &p : f.parameters) if (p.is_template_param()) ++cnt;
  return cnt;
}

static int count_template_kinds(const TemplateFunction &f) {
  set<string> kinds;
  for (const auto &p : f.parameters) if (p.is_template_param()) kinds.insert(p.name);
  return (int)kinds.size();
}

std::string resolve_call(const std::vector<TemplateFunction> &functions,
                         CallSite cs) {
  for (size_t i = 0; i < functions.size(); ++i) {
    const auto &f = functions[i];
    if (match_non_template(f, cs)) {
      return get_str(f);
    }
  }

  struct Cand {
    int idx;    // 在 functions 中的位置
    int tcnt;   // 模板参数数量（出现次数）
    int kcnt;   // 模板参数种类数
  };
  vector<Cand> cands;
  for (size_t i = 0; i < functions.size(); ++i) {
    const auto &f = functions[i];
    if (match_template(f, cs)) {
      cands.push_back({(int)i, count_template_params(f), count_template_kinds(f)});
    }
  }

  if (cands.empty()) return "Function not found.";

  sort(cands.begin(), cands.end(), [](const Cand &a, const Cand &b) {
    if (a.tcnt != b.tcnt) return a.tcnt < b.tcnt;
    if (a.kcnt != b.kcnt) return a.kcnt < b.kcnt;
    return a.idx < b.idx;
  });

  return get_str(functions[cands[0].idx]);
}
