#include <iostream>
#include <optional>
#include <vector>
#include <unordered_map>

class InMemoryDB {
    using Key   = std::string;
    using Value = int;
    using Time  = long long;

    private:
    std::unordered_multimap<Key, std::pair<Value,Time>> data;


    public:

    // ========= Stage 1: Core KV =========
    // Basic CRUD (time param accepted for consistency; Stage 1 can ignore it)
    void set(const Key& key, const Value& value, Time now = 0) {
        data.insert({key, {value, now}});
    }
    std::optional<Value> get(const Key& key, Time now = 0) const {
    }
    bool del(const Key& key, Time now = 0) {

    }

    // Queries / utilities
    bool exists(const Key& key, Time now = 0) const;
    size_t size(Time now = 0) const;       // live keys count
    void clear();                          // wipe everything (live + history if any)

    // Quality-of-life (often handy in tests)
    bool putIfAbsent(const Key& key, const Value& value, Time now = 0);
    bool replace(const Key& key, const Value& newValue, Time now = 0); // only if exists
    bool compareAndSet(const Key& key, const Value& expected, const Value& newValue, Time now = 0);

    // Bulk (optional but nice to have)
    size_t setAll(const std::vector<std::pair<Key,Value>>& items, Time now = 0);
    std::vector<std::optional<Value>> getAll(const std::vector<Key>& keys, Time now = 0) const;
    std::vector<Key> keys(Time now = 0) const;

    // ========= Stage 2: TTL =========
    // TTL write variants
    void setWithTTL(const Key& key, const Value& value, Time now, long long ttlSeconds);
    bool expire(const Key& key, Time now, long long ttlSeconds);   // set/replace TTL on existing key
    bool expireAt(const Key& key, Time expireAt);                  // absolute expiry time
    bool persist(const Key& key, Time now = 0);                    // remove TTL if present
    bool touch(const Key& key, Time now, long long extendBySeconds); // extend TTL on hot keys

    // TTL queries / cleanup
    // Returns: remaining seconds (>=0) if live, 0 if expires exactly now,
    //          std::nullopt if no such key or already expired.
    std::optional<long long> ttl(const Key& key, Time now) const;

    // Evict any entries determined expired at 'now'; returns # removed
    size_t purgeExpired(Time now);

    // ========= Stage 3: Point-in-time Reads (time travel) =========
    // Value that was effective at time 't' (considering overwrites, deletes, and TTL)
    std::optional<Value> getAt(const Key& key, Time t) const;
    bool existsAt(const Key& key, Time t) const;

    // Global snapshot-style queries (acceptable O(n) in OA)
    size_t sizeAt(Time t) const;              // number of keys live at t
    std::vector<Key> keysAt(Time t) const;    // keys live at t

    // Version/history inspection for debugging or tests
    // Return (ts, value) pairs for key versions in [from, to], up to 'limit' entries.
    std::vector<std::pair<Time, Value>>
    history(const Key& key,
            Time from = std::numeric_limits<Time>::min(),
            Time to   = std::numeric_limits<Time>::max(),
            size_t limit = SIZE_MAX) const;

    // Convenience: nearest versions relative to 't'
    std::optional<Value> getBefore(const Key& key, Time t) const;  // strictly before t
    std::optional<Value> getAfter (const Key& key, Time t) const;  // at or after t

    // ========= Stage 4: Deletion semantics & maintenance =========
    // Timestamped delete (alias of del with explicit now)
    bool delAt(const Key& key, Time now);

    // Range delete helpers (useful for prefix/keyspace tests; no-op semantics if not needed)
    // Note: prefix semantics only make sense if your keys are strings.
    size_t deleteByPrefix(const std::string& prefix, Time now);
    size_t deleteRangeLex(const Key& loInclusive, const Key& hiExclusive, Time now);

    // History maintenance (optional GC/compaction hooks)
    size_t compact(const Key& key, Time upToTime);      // prune old superseded versions ≤ upToTime
    size_t compactAll(Time upToTime, size_t budget = SIZE_MAX);

    // ========= Extras often seen in variants =========
    // Numeric convenience (if values are numeric strings; ignore if not used)
    // Returns new value or nullopt if key missing / non-numeric.
    std::optional<long long> incrBy(const Key& key, long long delta, Time now,
                                    std::optional<long long> ttlSeconds = std::nullopt);

    // Snapshots (lightweight handles; implementation can be a timestamp marker)
    struct Snapshot { Time t; };
    Snapshot snapshot(Time t) const;
    // Optionally materialize a full key->value view valid at time t (for testing):
    std::vector<std::pair<Key,Value>> dumpAt(Time t) const;

    // ======= Destructor / rule-of-five defaulted =======
    ~InMemoryDB() = default;
    InMemoryDB() = default;
    InMemoryDB(const InMemoryDB&) = default;
    InMemoryDB& operator=(const InMemoryDB&) = default;
    InMemoryDB(InMemoryDB&&) noexcept = default;
    InMemoryDB& operator=(InMemoryDB&&) noexcept = default;
};

int main() {

    return 0;
}