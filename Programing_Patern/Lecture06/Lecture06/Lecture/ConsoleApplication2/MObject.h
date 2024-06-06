class MObject {
public:
    MObject();
    virtual ~MObject();

    void print();

    virtual void update() = 0;
    virtual void render() = 0;
};







