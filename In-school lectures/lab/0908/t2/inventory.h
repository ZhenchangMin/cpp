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
        Thing things[20];
        int size;
    public:
        Inventory(){
            this->size = 0;
        }
        Inventory(Thing thing){
            this->things[0] = thing;
            this->size = 1;
        }
        int getStorage(int category, int quality);
        void setStorage(int category, int quality, int storage);
        void add(Thing thing);
        void inquiry(int category);
        void combine(int category, int a, int b, int c, int d);
        void use(int* numbers);
};