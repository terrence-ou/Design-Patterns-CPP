/*
2 - Open-close Principle
*/

#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

enum class Skill { CPP, Python, JavaScript, Bash };
enum class Education { Undergrad, Master, Doctor };

struct Candidate {
  string name{};
  Skill skill{};
  Education education{};
  int yrExperience{0};
};

/* ------ Bad filter implementation: ------ */
struct CandidateFilter {
  typedef vector<Candidate *> CandVec;

  // filter candidates by skill
  CandVec bySkill(CandVec candidates, Skill skill) {
    CandVec result{};
    for (Candidate *cand : candidates) {
      if (cand->skill == skill) result.push_back(cand);
    }
    return result;
  };

  // filter candidates by year of experience
  CandVec byExperience(CandVec candidates, int exp) {
    CandVec result{};
    for (Candidate *cand : candidates) {
      if (cand->yrExperience >= exp) result.push_back(cand);
    }
    return result;
  }

  // filter candidates by education level and year of experience
  CandVec byEduAndExp(CandVec candidates, Education edu, int exp) {
    CandVec result{};
    for (Candidate *cand : candidates) {
      if (cand->education == edu && cand->yrExperience >= exp)
        result.push_back(cand);
    }
    return result;
  }
};

/* ------ Better filter implementation: ------ */

// define specifications
template <typename T>
struct Specification {
  virtual ~Specification() = default;
  virtual bool isSatisfied(T *item) const = 0;
};

// and specification
template <typename T>
struct AndSpecification : Specification<T> {
  const Specification<T> &first{};
  const Specification<T> &second{};

  AndSpecification(const Specification<T> &first,
                   const Specification<T> &second)
      : first{first}, second{second} {};
  bool isSatisfied(T *item) const override {
    return first.isSatisfied(item) && second.isSatisfied(item);
  }
};

struct SkillSpecification : Specification<Candidate> {
  Skill skill;
  SkillSpecification(const Skill skill) : skill{skill} {};
  bool isSatisfied(Candidate *cand) const override {
    return cand->skill == skill;
  }
};

struct ExpSpecification : Specification<Candidate> {
  int exp;
  ExpSpecification(const int exp) : exp{exp} {};
  bool isSatisfied(Candidate *cand) const override {
    return cand->yrExperience >= exp;
  }
};

struct EduSpecification : Specification<Candidate> {
  Education eduLevel;
  EduSpecification(const Education eduLevel) : eduLevel{eduLevel} {};
  bool isSatisfied(Candidate *cand) const override {
    return cand->education == eduLevel;
  }
};

// define filter
template <typename T>
struct Filter {
  virtual vector<T *> filter(vector<T *> items, Specification<T> &spec) = 0;
};

struct BetterFilter : Filter<Candidate> {
  vector<Candidate *> filter(const vector<Candidate *> cands,
                             Specification<Candidate> &spec) override {
    vector<Candidate *> result{};
    for (Candidate *cand : cands) {
      if (spec.isSatisfied(cand)) result.push_back(cand);
    }
    return result;
  }
};

/* ------ Main program ------ */
int main() {
  Candidate tim{"Timothy", Skill::Python, Education::Master, 3};
  Candidate ken{"Kent", Skill::JavaScript, Education::Undergrad, 0};
  Candidate abi{"Abigail", Skill::CPP, Education::Doctor, 3};
  Candidate josh{"Joshua", Skill::Python, Education::Master, 5};
  const vector<Candidate *> allCands{&tim, &ken, &abi, &josh};

  // Bad filter example
  CandidateFilter cf;
  vector<Candidate *> candPython = cf.bySkill(allCands, Skill::Python);
  vector<Candidate *> candMasterExp =
      cf.byEduAndExp(allCands, Education::Master, 3);

  cout << "------ Bad filter ------" << endl;
  for (Candidate *cand : candPython)
    cout << cand->name << " knows Python" << endl;
  for (Candidate *cand : candMasterExp)
    cout << cand->name << " has Matser's degree and have 3 yrs experience."
         << endl;

  cout << "\n------ Better filter ------" << endl;
  BetterFilter bf{};
  SkillSpecification skillReq{Skill::JavaScript};
  EduSpecification eduReq{Education::Doctor};
  ExpSpecification expReq{3};
  AndSpecification<Candidate> eduExpReq{eduReq, expReq};

  vector<Candidate *> candJS = bf.filter(allCands, skillReq);
  vector<Candidate *> candEduExp = bf.filter(allCands, eduExpReq);
  for (Candidate *cand : candJS) {
    cout << cand->name << " knows Javascript." << endl;
  }
  for (Candidate *cand : candEduExp) {
    cout << cand->name << " has a Doctor's degree and 3 yrs experience."
         << endl;
  }

  return 0;
}
