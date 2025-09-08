class Thing
{
private:
        int category;
        int quality;
        int storage;
public:
        Thing(int c, int q, int s){
            this->category = c;
            this->quality = q;
            this->storage = s;
        }
        Thing(){
            this->category = 0;
            this->quality = 0;
            this->storage = 0;
        }
        int getCategory(){
            return this->category;
        }
        int getQuality(){
            return this->quality;
        }
        int getStorage(){
            return this->storage;
        }
        void setStorage(int s){
            this->storage = s;
        }
        void setCategory(int c){
            this->category = c;
        }
        void setQuality(int q){
            this->quality = q;
        }
};


class Inventory
{
    private:
        Thing things[80];
        int size;
    public:
        Inventory(){
            this->size = 0;
        }
        Inventory(Thing thing){
            this->things[0] = thing;
            this->size = 1;
        }
        void add(Thing thing);
        void inquiry(int category);
        void combine(int category, int a, int b, int c, int d);
        void use(int* numbers);
};