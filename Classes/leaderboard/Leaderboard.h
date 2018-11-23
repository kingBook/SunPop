#ifndef __LEADERBOARD_H__
#define __LEADERBOARD_H__
#define LEADERBOARD_CALLBACK_0(__selector__,__target__, ...) std::bind(&__selector__,__target__, ##__VA_ARGS__)
#define LEADERBOARD_CALLBACK_1(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, ##__VA_ARGS__)
#define LEADERBOARD_CALLBACK_2(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, ##__VA_ARGS__)
#define LEADERBOARD_CALLBACK_3(__selector__,__target__, ...) std::bind(&__selector__,__target__, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, ##__VA_ARGS__)
typedef std::function<void(bool succeed)> AuthenticateLocalUserCallback; // �û���¼�ص� 
typedef std::function<void(bool succeed)> SubmitScoreCallback; // �ύ�����ص� 
class Leaderboard{
public:
    static Leaderboard*getInstance();
    /**�û���¼*/
    void authenticateLocalUser(AuthenticateLocalUserCallback callback);
    /**��ʾ���а�*/
    void showLeaderboard();
    /**�ύ����*/
    void submitScore(int score, SubmitScoreCallback callback);

	/**��¼���*/
	void authenticateLocalUserFinish(bool succeed);
	/**�ύ�������*/
	void submitScoreFinish(bool succeed);
private:
    static Leaderboard*_instance;
	AuthenticateLocalUserCallback _authenticateLocalUserCallback;
    SubmitScoreCallback _submitScoreCallback;
};
#endif /* __LEADERBOARD_H__*/
