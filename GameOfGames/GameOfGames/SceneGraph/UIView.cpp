#include "UIView.h"

UIView::UIView(sf::Vector2i* newSize, std::string newTexture)
{
	setSize(newSize);
	setTexture(newTexture);
}

void UIView::onRemoveTexture()
{
	adjustBackGround();
}

void UIView::setSize(sf::Vector2i* newSize)
{
	size = newSize;

	adjustBackGround();
}

void UIView::adjustBackGround()
{
	sf::RenderTexture destinationTexture= sf::RenderTexture();

	destinationTexture.create(size->x,size->y);

	destinationTexture.clear(sf::Color::Green);

	if(texture)
	{
		

		int tileSize = texture->getSize().x/3;

		if (tileSize*2 > size->x || tileSize*2 > size->y)
		{
			std::cout<< "Size of view too small for texture selected.\n";
		}
		else
		{
			destinationTexture.clear();

			sf::Sprite tempSprite = sf::Sprite();
			tempSprite.setTexture(*texture);
			
			int heightToDraw = tileSize;
			int verticalFillSpace = size->y;
			int verticalDrawingPoint = 0;

			while (verticalFillSpace > 0)
			{
				int referenceVerticalPoint = 0;
				
				//are we filling vertical space?
				if(verticalDrawingPoint)
				{
					//are we filling the bottom?
					if (verticalFillSpace <= tileSize)
					{
						referenceVerticalPoint = tileSize*2;
					}
					else
					{
						referenceVerticalPoint = tileSize;
					}
				}

				//we draw the left chunk
				tempSprite.setPosition(0,verticalDrawingPoint);
				tempSprite.setTextureRect(sf::IntRect(0,referenceVerticalPoint,tileSize,heightToDraw));
				destinationTexture.draw(tempSprite);

				//the right chunk
				tempSprite.setPosition(size->x-tileSize,verticalDrawingPoint);
				tempSprite.setTextureRect(sf::IntRect(tileSize*2,referenceVerticalPoint,tileSize,heightToDraw));
				destinationTexture.draw(tempSprite);

				int horizontalFillingSpace = size->x - (tileSize*2);
				int horizontalDrawingPoint = tileSize;

				tempSprite.setTextureRect(sf::IntRect(tileSize,referenceVerticalPoint,tileSize,heightToDraw));

				//now we fill the horizontal gap
				while (horizontalFillingSpace > 0)
				{
					//are we drawing the last one?
					if (horizontalFillingSpace<tileSize)
					{
						tempSprite.setTextureRect(sf::IntRect(tileSize,referenceVerticalPoint,horizontalFillingSpace,heightToDraw));
					}

					tempSprite.setPosition(horizontalDrawingPoint,verticalDrawingPoint);
					destinationTexture.draw(tempSprite);

					horizontalDrawingPoint +=tileSize;
					horizontalFillingSpace -= tileSize;
				}

				verticalFillSpace -= tileSize;

				if (verticalFillSpace < tileSize)
				{
					verticalDrawingPoint += verticalFillSpace;
				}
				else
				{
					verticalDrawingPoint += tileSize;
				}
			}
		}
	}

	destinationTexture.display();

	if(finalTexture)
	{
		delete finalTexture;
	}

	finalTexture = new sf::Texture(destinationTexture.getTexture());

	sprite->setTexture(*finalTexture);
}

void UIView::onSetTexture()
{
	adjustBackGround();
}

UIView::~UIView(void)
{
	delete finalTexture;
	delete size;
}