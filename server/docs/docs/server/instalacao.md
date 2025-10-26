
## Instalando localmente

1. Clone o repositório:
    ```
    git clone https://github.com/diaslui/klinus
    ```
2. Crie e ative um ambiente virtual:
    ```
    python -m venv .venv
    source .venv/bin/activate  # Linux / macOS
    .venv\Scripts\activate     # Windows
    ```
3. Entre na pasta do servidor:
    ```
    cd server
    ```
4. Instale dependências:
    ```
    pip install -r requirements.txt
    ```
5. Configure variáveis de ambiente (exemplo .env):
    - SECRET_KEY
    - DATABASE_URL (ex: sqlite:///db.sqlite3 ou postgres://...)
    - ALLOWED_HOSTS

6. Execute migrações e crie um superusuário:
    ```
    python manage.py migrate
    python manage.py createsuperuser
    ```

## Rodando

- Em desenvolvimento:
  ```
  python manage.py runserver
  ```
- Para produção, use Gunicorn/uvicorn e configure reverse proxy (NGINX).