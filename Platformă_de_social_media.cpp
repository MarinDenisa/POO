#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
#include <string>
#include<algorithm>
#include<cstdio>
class Video {
protected:
    friend class VideoFactory;
    friend class StudyVideo;
    friend class AnimalVideo;
    friend class SportsVideo;

    std::string mVideoId;
    uint32_t mLikes, mDislikes, mViews;
    Video(const std::string& mVideoId, uint32_t mLikes, uint32_t mDislikes, uint32_t mViews) {
        this->mVideoId = mVideoId;
        this->mLikes = mLikes;
        this->mDislikes = mDislikes;
        this->mViews = mViews;
    }
public:
    std::string getId()const {
        return mVideoId;
    }
    uint32_t getDislikes()const {
        return mDislikes;
    }
    uint32_t getLikes()const {
        return mLikes;
    }
    uint32_t getViews()const {
        return mViews;
    }
    void setId(std::string& mVideoId1){
        mVideoId = mVideoId1;
    }
    void setDislikes(uint32_t mDislikes1) {
        mDislikes = mDislikes1;
    }
    void setLikes(uint32_t mLikes1) {
        mLikes = mLikes1;
    }
    void setViews(uint32_t mViews1) {
        mViews = mViews1;
    }
    double getSimpleScore() const {

        return getLikes() / float(getDislikes()) + 1 - 1 / float(getViews());
    }
    virtual double getAdvancedScore() const = 0;

    void print(bool simple) const {
        std::cout << mVideoId;
        if (simple == true)
            std::cout << std::fixed << std::setprecision(2) << getSimpleScore() << std::endl;
        else std::cout << std::fixed << std::setprecision(2) << getAdvancedScore() << std::endl;
    }
};
class StudyVideo : public Video {
public:
    StudyVideo(const std::string& mVideold, uint32_t mLikes, uint32_t mDislikes, uint32_t mViews) : Video(mVideold, mLikes, mDislikes, mViews) {

    }
    virtual double getAdvancedScore() const {
        return getSimpleScore() * 2;
    }
};
class AnimalVideo : public Video {
public:
    AnimalVideo(const std::string& mVideold, uint32_t mLikes, uint32_t mDislikes, uint32_t mViews) : Video(mVideold, mLikes, mDislikes, mViews) {

    }
    virtual double getAdvancedScore() const {
        return getSimpleScore() * 0.75;
    }
};

class SportsVideo : public Video {
public:
    SportsVideo(const std::string& mVideold, uint32_t mLikes, uint32_t mDislikes, uint32_t mViews) : Video(mVideold, mLikes, mDislikes, mViews) {

    }
    virtual double getAdvancedScore() const {
        return getSimpleScore() * 0.5;
    }
};

class VideoFactory : public Video {
public:
    std::string type;
    VideoFactory(const std::string type, std::string& mVideold, uint32_t mLikes, uint32_t mDislikes, uint32_t mViews) : Video(mVideold, mLikes, mDislikes, mViews) {
        this->type = type;
    }
    static Video* createVideo(const std::string& id, const std::string& type, uint32_t likes, uint32_t dislikes, uint32_t views) {
        if (type == "Animale") {
            AnimalVideo* result = new AnimalVideo(id, likes, dislikes, views);
            return result;
        }
        else {
            if (type == "Studiu") {
                StudyVideo* result = new StudyVideo(id, likes, dislikes, views);
                return result;
            }
            else {
                if (type == "Sport") {
                    SportsVideo* result = new SportsVideo(id, likes, dislikes, views);
                    return result;
                }
                else {
                    throw std::invalid_argument("Eroare");

                }
            }

        }
    }
};
bool static comparator(Video* a, Video* b) {
    if (a->getSimpleScore() == b->getSimpleScore())
        return a->getDislikes() > b->getDislikes();
    else return  a->getSimpleScore() < b->getSimpleScore();
}

bool static comparator1(Video* a, Video* b) {
        return a->getAdvancedScore() < b->getAdvancedScore();
    
}

int main()
{
    int n, lungime;
    std::string mVideold, type, cerinta;
    uint32_t mLikes, mDislikes, mViews;
    std::vector< Video*>v;
    std::cin >> n;
    lungime = n;
    while (n != 0) {
        std::cin >> mVideold >> type >> mViews >> mLikes >> mDislikes;
        if (type == "Animale") {
            v.push_back(new AnimalVideo(mVideold, mLikes, mDislikes, mViews));

        }
        else {
            if (type == "Studiu") {
                v.push_back(new StudyVideo(mVideold, mLikes, mDislikes, mViews));

            }
            else {
                if (type == "Sport") {
                    v.push_back(new SportsVideo(mVideold, mLikes, mDislikes, mViews));

                }
                else {
                    std::cout << "EROARE";
                    return 0;

                }
            }

        }
        n--;
    }
    std::cin >> cerinta;
    if (cerinta == "a") {
        sort(v.begin(), v.end(), comparator);
        for (auto i : v) {
            std::cout << i->getId() << " ";
            std::cout << std::fixed << std::setprecision(2) << i->getSimpleScore() << std::endl;

        }
    }
    if (cerinta == "b") {
        double scormed;
        for (auto i : v) {
            scormed = scormed + i->getSimpleScore();
        }
        scormed = scormed / lungime;
        for (auto i : v) {
            if (scormed < i->getSimpleScore()) {
                std::cout << i->getId() << " ";
                std::cout << std::fixed << std::setprecision(2) << i->getSimpleScore() << std::endl;
            }
        }
    }
    if (cerinta == "c") {
        while (std::cin >> mVideold) {
            std::cin >> type >> mViews >> mLikes >> mDislikes;
            int ok = 0;
            for (auto i : v) {
                if (i->getId() == mVideold) {
                    i->setViews(mViews);
                    i->setLikes(mLikes);
                    i->setDislikes(mDislikes);
                    ok = 1;
                }
            }
            if (ok == 0) {
                v.push_back(new SportsVideo(mVideold, mLikes, mDislikes, mViews));
            }
        }
        sort(v.begin(), v.end(), comparator);
        for (auto i : v) {
            std::cout << i->getId() << " ";
            std::cout << std::fixed << std::setprecision(2) << i->getSimpleScore() << std::endl;

        }
    }
    if (cerinta == "d") {
        sort(v.begin(), v.end(), comparator1);
        for (auto i : v) {
            std::cout << i->getId() << " ";
            std::cout << std::fixed << std::setprecision(2) << i->getAdvancedScore() << std::endl;

        }
    }
    return 0;
}
