#ifndef __LEADERBOARD_H__
#define __LEADERBOARD_H__
#define LEADERBOARD_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define LEADERBOARD_CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define LEADERBOARD_CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define LEADERBOARD_CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)
typedef std::function<void(bool succeed)> AuthenticateLocalUserCallback; // 用户登录回调 
typedef std::function<void(bool succeed)> SubmitScoreCallback; // 提交分数回调 
class Leaderboard{
public:
    static Leaderboard*getInstance();
    /**用户登录*/
    void authenticateLocalUser(AuthenticateLocalUserCallback callback);
    /**显示排行榜*/
    void showLeaderboard();
    /**提交分数*/
    void submitScore(int score, SubmitScoreCallback callback);

	/**登录完成*/
	void authenticateLocalUserFinish(bool succeed);
	/**提交分数完成*/
	void submitScoreFinish(bool succeed);
private:
    static Leaderboard*_instance;
	AuthenticateLocalUserCallback _authenticateLocalUserCallback;
    SubmitScoreCallback _submitScoreCallback;
};
#endif /* __LEADERBOARD_H__*/
