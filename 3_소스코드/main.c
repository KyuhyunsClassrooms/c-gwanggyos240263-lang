#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//학습 항목 정보를 저장할 구조체 정의
#define MAx_NAME_LENGTH 50
#define FILENAME "progress_data.txt"

typedef struct{
    int id;
    char subject[MAX_NAME_LENGTH]; //과목 이름을 넣을 공간
    int total_units; //전체분량(페이지 또는 챕터)
    int current_progress; //현재진도량
} LearningItem;

LearningItem items[100]; //최대 100개의 항목 저장
int item_count = 0; //현재 저장된 항목 수
int next_id = 1; //항목 ID를 고유하게 부여하기 위한 변수

//---함수 선언---
void load_data();
void save_data();
void display_menu();
void add_item();
void view_items();
void updata_progress();
void delete_item();
void calculate_and_display_stats();

//---메인 함수---
int main(){
    load_data();// 시작시 데이터 불러오기
    int choice;
    while (1) {
        display_menu();
        if(scanf("%d", &choice) !=1){
            //입력 오류 처리(문자 입력등)
            printf("\n잘못된 입력입니다. 다시 시도해주세요.\n";
                while(getchar() !='\n'); //입력 버퍼 지우기
                continue;
            }
            switch(choice){
                case 1:
                add_item();
                break;
                case 2:
                viwe_items();
                break;
                case 3:
                update_progress();
                break;
                case 4:
                delete_item();
                break;
                case 5:
                calculate_and_display_stats();
                break;
                case 6:
                save_data(); //종료 전 데이터 저장
                printf("\n데이터를 저장하고 프로그램을 종료합니다.\n");
                return 0;//프로그램 종료
                default:
                pritnf("\n 1부터 6까지 숫자를 입력해주세요. \n");
            }
        }
        return 0;
    }
    
    //---함수 구현---

    //메뉴표시
    void display_menu(){
    printf("\n===합습 진도 관리 프로그램 ===\n");
    pritnf("1. 새로운 학습 항목 추가\n");
    pritnf("2. 전체 항목 목록 보기 \n");
    printf("3. 진도 업데이트 \n");
    printf("4. 학습 항목 삭제 \n");
    printf("5. 진도율 통계 보기 \n");
    printf("6. 종료 및 저장 \n");
    printf("-------------------------------\n");
    printf("선 택 :");
    }

  //새로운  항목 추가

     void add_item() {
    if(item_count >= 100){
    prinf ("\n 최대 항목 개수(100개)에 도달했습니다.\n");
    return;
    }

    printf("\n---학습 항목 추가 ---\n");

    //ID 자동 할당 및 갱신
    items[item_count].id = next_id;

    printf(" 과목명 입력 (최대 %d자): ", MAX_NAME_LENGTH - 1);
    scanf("%49[^\n]", items[item_count].subject); //공백 포함 입력, 버퍼 오버 플로우 방지

    printf("전체 분량 (페이지 or 챕터 수) : ");
    scanf("%d", &items[item_count].total_units);

    printf("현재 진도: ");
    scanf("%d", &items[item_count].current_progress);

    //진도 유효성 검사
    if (items[item_count].current_progress >
    items[item_count]].total_units){
    items[item_count].current_progress = items[item_count].total_units;
    }
    else if (items[item_count].current_progress <0){
    items[item_count].current_progress = 0;
    }

    item_count++;
    printf("\n 항목이 성공적으로 추가되었습니다! ('%s' ID: %d)\n",
    items[item_count -1].subject, items[item_count -1].id);
    next_id++; //다음 항목에 부여할 ID증가
    }

    //학습 항목 삭제
    void delete_item(){
    int id;
    
    if(item_count ==0){
    printf("\n 삭제할 학습 항목이 없습니다.\n");
    return;
    }

    view_items();
    printf("\n---학습 항목 삭제 ---\n");
    printf("삭제할 항목의 ID를 입력하세요:");
    scanf("&d",&id);

    int found_index = -1;
    for(int i=0; i < item_count; i++){
    if(items[i].id == id){
    found_index = i;
    break;
    }
    }

    if(found_index == -1){
    printf("\n해당 ID(%d)를 가진 항목을 찾을 수 없습니다.\n", id);
    return;
    }

    //항목 삭제: 삭제된 항목 위치부터 배열의 끝까지 데이터를 한 칸씩 앞으로 당김
    printf("과목명 : '%s'을(를) 삭제합니다.\n", items[found_index].subject);

    for(int i = found_index; i < item_count - 1; i++){
    items[i] = items [i +1]; // 다음 항목의 내용을 현재 위치로 복사
    }

    item_count--; //전체 항목 수 1 감소

    printf("\n 항목이 성공적으로 삭제되었습니다.\n");
    }

    //전체 항목 목록 보기
    voud view_items(){
    if (item_count ==0){
    printf("\n 등록된 학습 항목이 없습니다.\n");
    return;
    }

    printf

    
    

       
   

            
    
