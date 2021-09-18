package app;

import lombok.Getter;
import lombok.Setter;

import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

@Getter
@Setter
class User {
    private String userId;
    private Map<String, User> followers;
    private Map<String, User> following;
    private boolean visited;

    public User() {
        this.followers = new HashMap<>();
        this.following = new HashMap<>();
    }

    public User(String userId) {
        this.userId = userId;
        this.followers = new HashMap<>();
        this.following = new HashMap<>();
    }

    public void addFollower(User user) {
        followers.put(user.getUserId(), user);
    }

    public void addFollowing(User user) {
        following.put(user.getUserId(), user);
    }

    @Override
    public String toString() {
        return userId;
    }

    public void resetVisited() {
        this.visited = false;
    }
}

public class SocialNetworkApp {
    public static Map<String, Integer> userIdToMaxFollowSequenceLength = new HashMap<>();

    public static void main(String[] args) {
        User A = new User("A");
        User B = new User("B");
        User C = new User("C");
        User D = new User("D");
        User E = new User("E");
        User F = new User("F");
        User G = new User("G");
        User H = new User("H");
        User I = new User("I");
        User J = new User("J");
        User K = new User("K");
        User L = new User("L");
        User M = new User("M");

        List<User> users = asList(A, B, C, D, E, F, G, H, I, J, K, L, M);

        addFollowingPair(A, B);
        addFollowingPair(A, I);
        addFollowingPair(B, C);
        addFollowingPair(B, J);
        addFollowingPair(C, D);
        addFollowingPair(D, E);
        addFollowingPair(D, M);
        addFollowingPair(D, A);
        addFollowingPair(D, K);
        addFollowingPair(E, F);
        addFollowingPair(E, M);
        addFollowingPair(F, G);
        addFollowingPair(H, A);
        addFollowingPair(L, A);

        System.out.println(getLongestFollowSequenceLength(users));
        System.out.println(getLongestFollowSequenceLength(F));
    }

    /**
     * Add "x follows y" pair.
     */
    public static void addFollowingPair(User x, User y) {
        x.addFollowing(y);
        y.addFollower(x);
    }

    public static List<User> asList(User... users) {
        List<User> result = new ArrayList<>();
        result.addAll(Arrays.asList(users));
        return result;
    }

    public static void resetVisited(List<User> users) {
        users.forEach(user -> user.resetVisited());
    }

    /**
     * Find out the length of the longest follow sequence from the given users.
     */
    public static int getLongestFollowSequenceLength(List<User> users) {
        int maxLength = 0;
        for (User user : users) {
            maxLength = Math.max(maxLength, getLongestFollowSequenceLength(user));
            resetVisited(users);
        }
        return maxLength;
    }

    /**
     * Find out the length of the longest follow sequence starting from the given user.
     */
    public static int getLongestFollowSequenceLength(User user) {
        if (user.isVisited()) {
            return 0;
        }
        user.setVisited(true);
        if (userIdToMaxFollowSequenceLength.containsKey(user.getUserId())) {
            return userIdToMaxFollowSequenceLength.get(user.getUserId());
        }
        if (user.getFollowing().isEmpty()) {
            userIdToMaxFollowSequenceLength.put(user.getUserId(), 0);
            return 0;
        }
        int maxLength = 0;
        for (User followingUser : user.getFollowing().values()) {
            maxLength = Math.max(maxLength, 1 + getLongestFollowSequenceLength(followingUser));
        }
        userIdToMaxFollowSequenceLength.put(user.getUserId(), maxLength);
        return maxLength;
    }
}