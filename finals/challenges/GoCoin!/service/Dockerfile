FROM golang:latest

# Install beego and the bee dev tool
RUN go get github.com/astaxie/beego 

# Create the directory where the application will reside
RUN mkdir /app

# Copy the application files (needed for production)
ADD src /app/MathApp
ADD src/views /app/views
ADD src/conf /app/conf

# Set the working directory to the app directory
WORKDIR /app/MathApp

# Expose the application on port 8080.
# This should be the same as in the app.conf file
EXPOSE 8080

COPY start.sh start.sh
RUN chmod +x start.sh

ENTRYPOINT ["./start.sh"]