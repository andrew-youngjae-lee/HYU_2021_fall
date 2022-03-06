# Delivery App 사용 설명서

## <seller.py>

### CLI 명령어 : 기능

### 'info' 명령어
python seller.py info [ID] : seller 정보 검색, password를 제외한 값 표시 
  - [ID] : 검색할 seller 식별 번호
### 'update' 명령어
python seller.py update [ID] [property] [value] : seller 정보 변경
  - [property] : 변경할 요소 ex) phone
  - [value] : 변경값

## <store.py>

### CLI 명령어 : 기능

### 'info' 명령어
python store.py info [ID] : store 정보 검색, 정보 표시
  - [ID] : 검색할 store 식별 번호
### 'menu' 명령어
python store.py menu [ID] : store가 제공하는 메뉴 검색
  - [ID] : menu를 검색할 store 식별 번호
### 'add_menu' 명령어
python store.py add_menu [ID] [menu_name] : store가 제공하는 메뉴 추가
  - [menu_name] : 추가할 menu 이름
### 'order' 명령어 
python store.py order [ID] [status] : 배달준비중-배달중-배달완료 상태별 주문 검색
  - [status] : (0 or pending)-배달 준비중, (1 or delivering)-배달중, (2 or delivered)-배달완료
### 'update_order' 명령어
python store.py update_order [ID] [order_id] [status] : [order_id]로 식별되는 주문의 상태를 [status]로 변경
### 'stat' 명령어
python store.py stat [ID] [start_date] [days] : 날짜별 총 주문건수 검색 (기준일로부터 일정 기간 동안)
  - [start_date] : 검색 기준 날짜
  - [days] : 검색 기준 날짜로부터의 검색 기간
### 'search' 명령어
python store.py search [ID] : 특정 가게의 모든 메뉴를 주문한 사람 검색

## <customer.py>

### CLI 명령어 : 기능

### 'info' 명령어
python customer.py info [ID] : customer 정보 검색
  - [ID] 검색할 customer의 식별 번호
### 'address' 명령어
python customer.py address [ID] [options] [args]
  - no [options]&[args] : [ID]로 식별되는 customer의 모든 주소 검색
  - [options] : (-c or --create)-새로운 주소 추가, (-e or --edit)-기존 주소 중 하나를 변경, (-r, --remove)-기존 주소 중 하나를 삭제
  - [args] : '추가'의 경우 추가할 주소, '변경'의 경우 변경할 주소 번호와 변경값(주소), '삭제'의 경우 삭제할 주소 번호
### 'pay' 명령어
python customer.py pay [ID] [options] [args]
  - no [options]&[args] : [ID]로 식별되는 customer의 모든 결제 정보 표시
  - [options] : (--add-account)-새로운 결제 계좌 정보 추가, (--add-card)-새로운 결제 카드 정보 추가, (-r or --remove)-기존 결제 정보 중 하나를 삭제
  - [args] : '추가'의 경우 계좌 번호 혹은 카드 번호, '변경'의 경우 결제수단 번호와 변경값, '삭제'의 경우 삭제할 결제수단 번호
### 'search' 명령어
python customer.py search [ID] [-a|-o|-l] [args]
  - [-a] : 주문 가능 여부 상관없이 모든 store 표시
  - [-o] : 정렬 기준 (-o 0)-store 이름 사전순, (-o 1)-store 주소 사전순, (-o 2)-customer와의 거리순(가까운 store부터 지정된 개수만큼 표시)
  - [-l] : 검색할 store 개수(기본값 10)
### 'store' 명령어
python store [ID] [store_id] : [ID]로 식별되는 customer가 [store_id]로 식별되는 store의 메뉴를 검색하고 주문 중 가게로 선택








